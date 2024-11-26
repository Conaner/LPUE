#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <mutex>
#include <StorageLayer.h>

// #define VALUE_SIZE 1024

class ReadWriteBuffer
{
public:
    // 写 Key 缓冲区
    off_t writeKey(const std::string &key);

    // 写 Value 缓冲区
    off_t writeValue(const std::string &value);
    // 从磁盘读取 Value
    std::string readValue(off_t offset);

private:
    static const size_t MAX_BUFFER_SIZE = 500000; // 缓冲区容量
    std::vector<std::string> keyBuffer;           // Key 缓冲
    std::vector<std::string> valueBuffer;         // Value 缓冲
    std::string readBuffer;                       // Read 缓冲

    std::string keyFilePath = "key_file.dat";     // Key 存储路径
    std::string valueFilePath = "value_file.dat"; // Value 存储路径

    off_t keyFileOffset = 0;   // Key 文件偏移量
    off_t valueFileOffset = 0; // Value 文件偏移量
    std::mutex bufferMutex;    // 线程安全锁
    int VALUE_SIZE = 10;
    int READ_BUFFER_MAX_SIZE = 10000;
    StorageLayer storageLayer;
    // 刷写缓冲区到磁盘
    void flushBufferToDisk(std::vector<std::string> &buffer, const std::string &filePath, off_t &offset);
};
