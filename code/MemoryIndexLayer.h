#include <unordered_map>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <list>
#include "ReadWriteBuffer.h"

class MemoryIndexLayer
{
public:
    // 插入新键值
    bool put(const std::string &key, const std::string &value);

    // 获取值偏移量
    off_t getOffset(const std::string &key);

    // 删除键值对
    bool del(const std::string &key);

    std::string get(const std::string &key);
    void MemoryIndexLayer::updateLRUCache(const std::string &key, const std::string &value);

private:
    std::unordered_map<std::string, off_t> index; // key -> 偏移量
    std::mutex mutex;                             // 保证多线程安全
    ReadWriteBuffer buffer;                       // 读写缓冲
    size_t lruCapacity;                         // LRU 缓存容量
    std::list<std::string> lruList;             // LRU 缓存访问列表
    std::unordered_map<std::string, std::pair<std::string, std::list<std::string>::iterator>> lruCache;  // LRU 缓存
};
