#include <unordered_map>
#include <string>
#include <mutex>
#include <list>
#include "ReadWriteBuffer.h"

class MemoryIndexLayer
{
public:
    // 插入新键值
    bool put(const std::int64_t &key, const std::string &value);

    // 获取值偏移量
    off_t getOffset(const std::int64_t &key);

    // 删除键值对
    bool del(const std::int64_t &key);

    std::string get(const std::int64_t &key);
    void updateLRUCache(const std::int64_t &key, const std::string &value);

private:
    std::unordered_map<std::int64_t, off_t> index;                                                        // key -> 偏移量
    std::mutex mutex;                                                                                     // 保证多线程安全
    ReadWriteBuffer buffer;                                                                               // 读写缓冲
    size_t lruCapacity = 100;                                                                                   // LRU 缓存容量
    std::list<std::int64_t> lruList;                                                                      // LRU 缓存访问列表
    std::unordered_map<std::int64_t, std::pair<std::string, std::list<std::int64_t>::iterator>> lruCache; // LRU 缓存
};
