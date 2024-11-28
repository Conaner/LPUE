#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef STORAGE_LAYER_H  // 如果未定义 STORAGE_LAYER_H
#define STORAGE_LAYER_H  // 定义 STORAGE_LAYER_H
class StorageLayer
{
public:
    // StorageLayer(const std::string &path);

    // ~StorageLayer();

    // 写入数据
    // void writeData(const std::string &data, off_t offset);

    void writeData(off_t offset, const char *data, size_t dataSize);
    // static void writeValueData(const std::string &filePath, off_t offset, const char *data, size_t size);
    // void flushValueBufferToDisk(off_t &valueFileOffset);
    // 读取数据
    std::string readData(off_t offset);

private:
    //     std::string filePath; // 存储文件路径
    //     int fd;               // 文件描述符
    std::string k_v_FilePath = "key_value_file.dat"; // 存储路径
};

#endif // STORAGE_LAYER_H  // 结束宏保护