#include "StorageLayer.h"
#include <fstream>

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
std::string StorageLayer::readData(off_t offset)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open value file for reading: " + filePath);
    }

    file.seekg(offset);
    std::string sizeStr;
    char ch;
    while (file.get(ch))
    {
        if (ch == ':')
        {
            break;
        }
        sizeStr += ch;
    }
    size_t dataSize = 0;
    try
    {
        dataSize = std::stoul(sizeStr); // 解析出数据的长度
    }
    catch (const std::exception &e)
    {
        file.close();
        throw std::runtime_error("Invalid serialized data format at offset " + std::to_string(offset) + ": " + e.what());
    }
    // 读取实际数据
    std::string value(dataSize, '\0');
    file.read(&value[0], dataSize);

    file.close();

    // 检查实际读取的大小是否匹配
    if (value.size() != dataSize)
    {
        throw std::runtime_error("Failed to read complete data at offset " + std::to_string(offset));
    }

    return value; 
    // pread(fd, buffer, size, offset);
    // return std::string(buffer, size);
}

