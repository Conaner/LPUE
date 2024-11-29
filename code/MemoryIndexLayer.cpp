#include "MemoryIndexLayer.h"
#include <iostream>

void printIndex(const std::unordered_map<std::int64_t, off_t> &index)
{
    // 遍历 unordered_map
    for (const auto &entry : index)
    {
        std::cout << "Key: " << entry.first << ", Value: " << entry.second << std::endl;
    }
}

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
        printIndex(index);
        if (keyOffset > 0)
            keyOffset = 1; // 为了编译通过（需要修改）
        updateLRUCache(key, value);
        return true;
    }
    return false; // key 已存在
}

std::string MemoryIndexLayer::get(const std::int64_t &key)
{
    std::unique_lock<std::mutex> lock(mutex);
    // 1. 检查LRU缓存
    std::cout << "检查LRU缓存" << std::endl; // 调试信息
    auto lruIt = lruCache.find(key);
    if (lruIt != lruCache.end())
    {
        // 移动到LRU头部
        lruList.splice(lruList.begin(), lruList, lruIt->second.second);
        return lruIt->second.first;
    }
    std::cout << "检查HashMap" << std::endl; // 调试信息
    // 2. 不在LRU缓存，查HashMap
    auto indexIt = index.find(key);
    if (indexIt != index.end())
    {
        // 从磁盘读取
        std::string value = buffer.readValue(indexIt->second); // 返回的数据是  “大小:值”, 需要进一步处理
        // 处理
        size_t delimiterPos = value.find(':');
        if (delimiterPos != std::string::npos)
        {
            value = value.substr(delimiterPos + 1); // 获取 ":" 后面的部分
        }
        // 更新 LRU 缓存
        updateLRUCache(key, value);
        return value;
    }
    // 3. 数据不存在
    std::cout << "数据不存在" << std::endl; // 调试信息
    return "";
}

// 获取值偏移量
off_t MemoryIndexLayer::getOffset(const std::int64_t &key)
{
    // std::shared_lock<std::mutex> lock(mutex);
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
        // printf("lrulist size=%ld lrucapacity = %ld\n", lruList.size(), lruCapacity);
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