#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <mutex>
#include <unordered_map>
#include "StorageLayer.h"

// #define VALUE_SIZE 1024

class ReadWriteBuffer
{
public:
    // 写 Key 缓冲区
    off_t writeKey(const std::int64_t &key);

    // 写 Value 缓冲区
    off_t writeValue(const std::string &value);

    // 从磁盘读取 Value
    std::string readValue(off_t offset);
    
    // 刷写缓冲区到磁盘
    // template <typename T>
    void flushKeyBufferToDisk();

    void flushValueBufferToDisk();

private:
    static const size_t MAX_BUFFER_SIZE = 500000; // 缓冲区容量
    std::vector<std::int64_t> keyBuffer;          // Key 缓冲
    // std::vector<std::string> valueBuffer;         // Value 缓冲
    std::unordered_map<off_t, std::string> valueBuffer; // Value 缓冲

    static const size_t MAX_LRU_SIZE = 100;            // 最大 LRU 缓存大小
    std::unordered_map<off_t, std::string> readBuffer; // 存储 offset -> value
    size_t currentSize = 0;                            // 当前缓存大小
    // std::string readBuffer;                       // Read 缓冲

    // std::string keyFilePath = "key_file.dat";     // Key 存储路径
    // std::string valueFilePath = "value_file.dat"; // Value 存储路径
    // std::string k_v_FilePath = "key_value_file.dat"; // 存储路径

    off_t currentKeyOffset = 0;                   // Key 当前偏移量
    off_t keyFileOffset = 0;                      // Key 文件偏移量
    off_t currentvalueOffset = 10 * 1024 * 1024; // Value 当前偏移量
    off_t valueFileOffset = 10 * 1024 * 1024;    // Value 文件偏移量

    std::mutex bufferMutex; // 线程安全锁
    // int VALUE_SIZE = 10;
    int READ_BUFFER_MAX_SIZE = 10000;
    StorageLayer storageLayer;
};
