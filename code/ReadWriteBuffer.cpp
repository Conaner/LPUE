#include "ReadWriteBuffer.h"

#include <cstring>
#include <iostream>
#include <algorithm>

// 写 Key 缓冲区
off_t ReadWriteBuffer::writeKey(const std::int64_t &key)
{
    std::unique_lock<std::mutex> lock(bufferMutex);
    keyBuffer.push_back(key);
    currentKeyOffset += sizeof(key); // 后续查找的时候根据偏移量读取！！
    if (keyBuffer.size() >= MAX_BUFFER_SIZE)
    {
        flushKeyBufferToDisk();
    }
    return currentKeyOffset - sizeof(key); // 返回当前写入偏移量
}

// 写 Value 缓冲区
off_t ReadWriteBuffer::writeValue(const std::string &value)
{
    std::unique_lock<std::mutex> lock(bufferMutex);
    std::string serializedValue = std::to_string(value.size()) + ":" + value;
    // std::cout << "Writing Value at Offset: " << currentvalueOffset << ", Serialized Value: " << serializedValue << std::endl;
    // std::cout << "Serialized Value: " << serializedValue <<serializedValue.size()<< std::endl;    // 调试信息
    valueBuffer[currentvalueOffset] = serializedValue;
    // valueBuffer.push_back(serializedValue);
    // std::cout << "currentvalueOffset Value: " << currentvalueOffset <<" "<< serializedValue.size()<< std::endl;    // 调试信息
    currentvalueOffset += serializedValue.size();
    // std::cout << "currentvalueOffset Value: " << currentvalueOffset;
    if (valueBuffer.size() >= MAX_BUFFER_SIZE)
    {
        flushValueBufferToDisk();
    }
    return currentvalueOffset - serializedValue.size(); // 返回当前写入偏移量
}

// 从磁盘读取 Value
std::string ReadWriteBuffer::readValue(off_t offset)
{
    // char buffer[VALUE_SIZE];
    // int fd = open(valuek_v_FilePath.c_str(), O_RDONLY);
    // pread(fd, buffer, VALUE_SIZE, offset); // 根据偏移量读取
    // close(fd);
    // return std::string(buffer);
    if (offset < 0)
    {
        throw std::invalid_argument("Invalid offset: offset cannot be negative");
    }

    std::unique_lock<std::mutex> lock(bufferMutex);
    // 1. 检查 readBuffer 是否存在对应数据
    std::cout << "检查 readBuffer 是否存在对应数据" << std::endl;
    auto it = readBuffer.find(offset);
    if (it != readBuffer.end())
        return it->second;

    // 2. 检查 valueBuffer 缓冲区
    std::cout << "检查 valueBuffer 缓冲区" << std::endl;
    auto valueIt = valueBuffer.find(offset);
    if (valueIt != valueBuffer.end())
    {
        if (static_cast<int>(readBuffer.size()) >= READ_BUFFER_MAX_SIZE)
        {
            // LRU 缓存淘汰策略，清除最老的记录
            readBuffer.erase(readBuffer.begin());
        }
        readBuffer[offset] = valueIt->second; // 加入缓存
        return valueIt->second;
    }
    // 3. 调用 StorageLayer::readData 读取磁盘数据
    std::cout << "调用 StorageLayer::readData 读取磁盘数据" << std::endl;
    std::string data = storageLayer.readData(offset);
    // std::cout << "data:" << data << std::endl; // 调试信息
    if (data.empty())
        return "";
    if (static_cast<int>(readBuffer.size()) >= READ_BUFFER_MAX_SIZE)
        readBuffer.erase(readBuffer.begin());
    readBuffer[offset] = data;
    return data;
    // try
    // {
    //     off_t currentOffset = offset;

    //     while (true)
    //     {
    //         // 从存储层读取数据
    //         std::string data = storageLayer.readData(offset, VALUE_SIZE);
    //         if (readBuffer.empty())
    //             return "";

    //         if (readBuffer.find(std::to_string(offset)) != std::string::npos)
    //         {
    //         }
    //     }

    //     // 检查读取数据是否超出大小限制
    //     if (data.size() > VALUE_SIZE)
    //     {
    //         throw std::runtime_error("Read data size exceeds the VALUE_SIZE limit.");
    //     }

    //     // 将数据加入 readBuffer
    //     // if (readBuffer.size() + 1 > READ_BUFFER_MAX_SIZE)
    //     // {
    //     //     readBuffer.clear(); // 清空 readBuffer
    //     // }
    //     // readBuffer.push_back(data);
    //     // return data;

    //     // 如果找到目标数据，返回
    //     if (!dataBlock.empty())
    //     {
    //         return targetData;
    //     }

    //     // 如果未找到目标数据，返回空字符串
    //     return "";
    // }
    // catch (const std::exception &e)
    // {
    //     std::cerr << "Error reading from StorageLayer: " << e.what() << std::endl;
    //     return ""; // 返回空字符串表示读取失败
    // }
}

// 刷写缓冲区到磁盘
// template <typename T>
void ReadWriteBuffer::flushKeyBufferToDisk()
{
    std::unique_lock<std::mutex> lock(bufferMutex);
    const off_t MAX_KEY_REGION_SIZE = 100 * 1024 * 1024;
    if (currentKeyOffset > MAX_KEY_REGION_SIZE)
    {
        throw std::runtime_error("Key region exceeds 100 MB limit.");
    }
    storageLayer.writeData(keyFileOffset,
                           reinterpret_cast<const char *>(keyBuffer.data()),
                           currentKeyOffset - keyFileOffset);

    // file.close();
    keyFileOffset = currentKeyOffset;
    // 清空 keyBuffer
    keyBuffer.clear();
}

// void ReadWriteBuffer::flushValueBufferToDisk(off_t &valueFileOffset)
// {
//     std::ofstream file(k_v_FilePath, std::ios::binary | std::ios::app);
//     if (!file.is_open())
//     {
//         throw std::runtime_error("Failed to open file for writing: " + k_v_FilePath);
//     }

//     // 按偏移量排序，将数据序列化写入文件
//     std::vector<std::pair<off_t, std::string>> sortedBuffer(valueBuffer.begin(), valueBuffer.end());
//     std::sort(sortedBuffer.begin(), sortedBuffer.end());

//     for (const auto &[offset, value] : sortedBuffer)
//     {
//         if (offset < valueFileOffset) // 避免覆盖已有数据
//         {
//             continue;
//         }

//         file.seekp(offset);                      // 定位到文件偏移位置
//         file.write(value.c_str(), value.size()); // 写入序列化数据
//     }

//     file.close();

//     // 清空内存中的 valueBuffer
//     valueBuffer.clear();

//     // 更新当前文件偏移量（确保与磁盘数据同步）
//     if (!sortedBuffer.empty())
//     {
//         const auto &[lastOffset, lastValue] = sortedBuffer.back();
//         valueFileOffset = lastOffset + lastValue.size();
//     }
// }

void ReadWriteBuffer::flushValueBufferToDisk()
{
    // 1. 将 valueBuffer 中的数据序列化为一个大的字节数组
    std::vector<char> buffer;
    std::vector<std::pair<off_t, std::string>> sortedBuffer(valueBuffer.begin(), valueBuffer.end());

    // 按照 off_t 升序排序
    std::sort(sortedBuffer.begin(), sortedBuffer.end(),
              [](const std::pair<off_t, std::string> &a, const std::pair<off_t, std::string> &b)
              {
                  return a.first < b.first; // 按 off_t 排序
              });

    for (const auto &[offset, value] : sortedBuffer)
    {
        buffer.insert(buffer.end(), value.begin(), value.end());
    }

    // // 打印 buffer 中的数据
    // std::cout << "Buffer data: ";
    // for (char c : buffer)
    // {
    //     std::cout << c; // 输出每个字符
    // }
    // std::cout << std::endl;

    // 2. 使用 StorageLayer 写入数据
    storageLayer.writeData(valueFileOffset, buffer.data(), buffer.size());

    // 3. 清空 valueBuffer
    valueBuffer.clear();

    // 4. 更新 valueFileOffset
    valueFileOffset += buffer.size();
}