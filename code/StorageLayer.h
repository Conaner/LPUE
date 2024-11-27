#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

class StorageLayer
{
public:
    StorageLayer(const std::string &path);

    ~StorageLayer();

    // 写入数据
    void writeData(const std::string &data, off_t offset);
    void flushValueBufferToDisk(off_t &valueFileOffset);
    // 读取数据
    std::string readData(off_t offset);

private:
    std::string filePath; // 存储文件路径
    int fd;               // 文件描述符
};