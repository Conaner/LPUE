#include "ReadWriteBuffer.h"

// 写 Key 缓冲区
off_t ReadWriteBuffer::writeKey(const std::string &key)
{
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
    char buffer[VALUE_SIZE];
    int fd = open(valueFilePath.c_str(), O_RDONLY);
    pread(fd, buffer, VALUE_SIZE, offset); // 根据偏移量读取
    close(fd);
    return std::string(buffer);
}

// 刷写缓冲区到磁盘
void ReadWriteBuffer::flushBufferToDisk(std::vector<std::string> &buffer, const std::string &filePath, off_t &offset)
{
    int fd = open(filePath.c_str(), O_CREAT | O_WRONLY, 0644);
    for (const auto &entry : buffer)
    {
        ssize_t written = pwrite(fd, entry.c_str(), entry.size(), offset);
        offset += written;
    }
    buffer.clear(); // 清空缓冲区
    close(fd);
}
