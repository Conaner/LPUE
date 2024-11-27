#include "MemoryIndexLayer.h"

// 插入新键值

bool MemoryIndexLayer::put(const std::int64_t &key, const std::string &value)
{
    std::unique_lock<std::mutex> lock(mutex);
    if (index.find(key) == index.end())
    {
        // 写入缓冲区
        off_t keyOffset = buffer.writeKey(key);
        off_t valueOffset = buffer.writeValue(value);
        index[key] = valueOffset;
        updateLRUCache(key, value);
        return true;
    }
    return false; // key 已存在
}

std::string MemoryIndexLayer::get(const std::int64_t &key)
{
    std::unique_lock<std::mutex> lock(mutex);
    // 1. 检查LRU缓存
    auto lruIt = lruCache.find(key);
    if (lruIt != lruCache.end())
    {
        // 移动到LRU头部
        lruList.splice(lruList.begin(), lruList, lruIt->second.second);
        return lruIt->second.first;
    }
    // 2. 不在LRU缓存，查HashMap
    auto indexIt = index.find(key);
    if (indexIt != index.end())
    {
        // 从磁盘读取
        std::string value = buffer.readValue(indexIt->second);
        // 更新 LRU 缓存
        updateLRUCache(key, value);
        return value;
    }
    // 3. 数据不存在
    return "";
}

// 获取值偏移量
off_t MemoryIndexLayer::getOffset(const std::int64_t &key)
{
    std::shared_lock<std::mutex> lock(mutex);
    auto it = index.find(key);
    if (it != index.end())
    {
        return it->second;
    }
    return -1; // key 不存在
}

// 删除键值对
bool MemoryIndexLayer::del(const std::int64_t &key)
{
    std::unique_lock<std::mutex> lock(mutex);
    // 从内存索引中删除
    auto it = index.find(key);
    if (it != index.end())
    {
        index.erase(it);

        // 从 LRU 缓存中删除
        lruCache.erase(key);
        lruList.remove(key);

        return true;
    }
    return false; // key 不存在
}


void MemoryIndexLayer::updateLRUCache(const std::int64_t &key, const std::string &value)
{
    auto lruIt = lruCache.find(key);

    if (lruIt != lruCache.end())
    {
        // Key 已在缓存中，移动到 LRU 头部
        lruList.splice(lruList.begin(), lruList, lruIt->second.second);
        lruIt->second.first = value;
    }
    else
    {
        // Key 不在缓存中，插入到缓存
        if (lruList.size() >= lruCapacity)
        {
            // LRU 缓存已满，移除最久未使用的键
            std::int64_t oldKey = lruList.back();
            lruList.pop_back();
            lruCache.erase(oldKey);
        }
        // 插入新键
        lruList.push_front(key);
        lruCache[key] = {value, lruList.begin()};
    }
}