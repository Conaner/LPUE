#include "MemoryIndexLayer.h"

// 插入新键值
bool MemoryIndexLayer::put(const std::string &key, const std::string &value)
{
    std::unique_lock<std::mutex> lock(mutex);
    if (index.find(key) == index.end())
    {
        // 写入缓冲区
        off_t keyOffset = buffer.writeKey(key);
        off_t valueOffset = buffer.writeValue(value);
        index[key] = valueOffset;
        return true;
    }
    return false; // key 已存在
}

// 获取值偏移量
off_t MemoryIndexLayer::getOffset(const std::string &key)
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
bool MemoryIndexLayer::del(const std::string &key)
{
    std::unique_lock<std::mutex> lock(mutex);
    return index.erase(key) > 0;
}
