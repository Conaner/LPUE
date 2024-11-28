#include "StorageLayer.h"
#include <fstream>
#include <iostream>

// StorageLayer::StorageLayer(const std::string &path) : k_v_FilePath(path)
// {
//     fd = open(k_v_FilePath.c_str(), O_CREAT | O_RDWR, 0644);
// }

// StorageLayer::~StorageLayer()
// {
//     close(fd);
// }

// 写入数据
// void StorageLayer::writeData(const std::string &data, off_t offset)
// {
//     pwrite(fd, data.c_str(), data.size(), offset);
// }

void StorageLayer::writeData( off_t offset, const char *data, size_t dataSize)
{
    // 打开文件，以二进制模式写入
    std::ofstream file(k_v_FilePath, std::ios::binary | std::ios::in | std::ios::out);
    if (!file.is_open())
    {
        throw std::ios_base::failure("Failed to open file for writing: " + k_v_FilePath);
    }

    // 移动文件写指针到指定偏移量
    file.seekp(offset, std::ios::beg);
    if (!file)
    {
        throw std::ios_base::failure("Failed to seek to offset in file: " + k_v_FilePath);
    }

    // 写入数据
    file.write(data, dataSize);
    if (!file)
    {
        throw std::ios_base::failure("Failed to write data to file: " + k_v_FilePath);
    }

    file.close();
}

// void StorageLayer::writeValueData(const std::string &k_v_FilePath, off_t offset, const char *data, size_t size){
    
// }

// 读取数据
std::string StorageLayer::readData(off_t offset)
{   
    std::cout << "offset: " << offset << std::endl;  // 调试信息
    std::ifstream file(k_v_FilePath, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open value file for reading: " + k_v_FilePath);
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
    std::cout << "Size String: '" << sizeStr << "'" << std::endl;   // 调试信息
    size_t dataSize ;
    try
    {
        dataSize = std::stoul(sizeStr); // 解析出数据的长度
        std::cout << "dataSize: " << dataSize << std::endl;  // 调试信息
    }
    catch (const std::exception &e)
    {
        file.close();
        std::cout << "dataSize: " << dataSize << std::endl;  // 调试信息
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

