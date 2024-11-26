#include "ReadWriteBuffer.h"
#include <cstring>
#include <iostream>
#include <algorithm>

// 写 Key 缓冲区
off_t ReadWriteBuffer::writeKey(const std::string &key)
{
    std::unique_lock<std::mutex> lock(bufferMutex);
    keyBuffer.push_back(key);
    if (keyBuffer.size() >= MAX_BUFFER_SIZE)
    {
        flushBufferToDisk(keyBuffer, keyFilePath, keyFileOffset);
    }
    return keyFileOffset; // 返回当前写入偏移量
}

// 写 Value 缓冲区
off_t ReadWriteBuffer::writeValue(const std::string &value)
{
    std::unique_lock<std::mutex> lock(bufferMutex);
    valueBuffer.push_back(value);
    if (valueBuffer.size() >= MAX_BUFFER_SIZE)
    {
        flushBufferToDisk(valueBuffer, valueFilePath, valueFileOffset);
    }
    return valueFileOffset; // 返回当前写入偏移量
}

// 从磁盘读取 Value
std::string ReadWriteBuffer::readValue(off_t offset)
{
    // char buffer[VALUE_SIZE];
    // int fd = open(valueFilePath.c_str(), O_RDONLY);
    // pread(fd, buffer, VALUE_SIZE, offset); // 根据偏移量读取
    // close(fd);
    // return std::string(buffer);
    if (offset < 0)
    {
        throw std::invalid_argument("Invalid offset: offset cannot be negative");
    }

    std::unique_lock<std::mutex> lock(bufferMutex);
    // 1. 检查 readBuffer 是否存在对应数据
    for (const auto &entry : readBuffer)
    {
        if (entry == std::to_string(offset))
        {
            return entry; // 如果存在，直接返回
        }
    }

    // 2. 检查 valueBuffer 缓冲区
    for (const auto &entry : valueBuffer)
    {
        if (valueFileOffset == offset)
        {
            // 将数据加入 readBuffer 并返回
            // if (readBuffer.size() + 1 > READ_BUFFER_MAX_SIZE)
            // {
            //     readBuffer.clear(); // 清空 readBuffer
            // }
            // readBuffer.push_back(entry);
            return entry;
        }
    }
    // 3. 调用 StorageLayer::readData 读取磁盘数据
    try
    {
        size_t blockSize = VALUE_SIZE;
        off_t currentOffset = offset;
                
        while (true){
            // 从存储层读取数据
            readBuffer  = storageLayer.readData(currentOffset, VALUE_SIZE);
            if(readBuffer.empty())break;

            if (readBuffer.find(std::to_string(offset)) != std::string::npos)
            {
                
            }

        }
        

        // 检查读取数据是否超出大小限制
        if (data.size() > VALUE_SIZE)
        {
            throw std::runtime_error("Read data size exceeds the VALUE_SIZE limit.");
        }

        // 将数据加入 readBuffer
        // if (readBuffer.size() + 1 > READ_BUFFER_MAX_SIZE)
        // {
        //     readBuffer.clear(); // 清空 readBuffer
        // }
        // readBuffer.push_back(data);
        // return data;

        // 如果找到目标数据，返回
        if (!dataBlock.empty())
        {
            return targetData;
        }

        // 如果未找到目标数据，返回空字符串
        return "";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error reading from StorageLayer: " << e.what() << std::endl;
        return ""; // 返回空字符串表示读取失败
    }
}

// 刷写缓冲区到磁盘
void ReadWriteBuffer::flushBufferToDisk(std::vector<std::string> &buffer, const std::string &filePath, off_t &offset)
{
    int fd = open(filePath.c_str(), O_CREAT | O_WRONLY, 0644);
    for (const auto &entry : buffer)
    {
        ssize_t written = pwrite(fd, entry.c_str(), entry.size(), offset);
        if (written < 0)
        {
            close(fd);
            throw std::runtime_error("Failed to write to file: " + filePath + ", error: " + std::string(strerror(errno)));
        }
        offset += written;
    }
    buffer.clear(); // 清空缓冲区
    close(fd);
}
