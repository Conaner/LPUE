#include "StorageLayer.h"

StorageLayer::StorageLayer(const std::string &path) : filePath(path)
{
    fd = open(filePath.c_str(), O_CREAT | O_RDWR, 0644);
}

StorageLayer::~StorageLayer()
{
    close(fd);
}

// 写入数据
void StorageLayer::writeData(const std::string &data, off_t offset)
{
    pwrite(fd, data.c_str(), data.size(), offset);
}

// 读取数据
std::string StorageLayer::readData(off_t offset, size_t size)
{
    char buffer[size];
    pread(fd, buffer, size, offset);
    return std::string(buffer, size);
}
