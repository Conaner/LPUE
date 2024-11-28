#include <iostream>
#include <cstring>
#include <cassert>
#include "code/StorageLayer.h"

void testStorageLayer()
{
    StorageLayer storageLayer;

    // 测试写入数据
    const char *writeData = "21:Hello, Storage Layer!";
    off_t offset = 0;  // 从文件的开始处写入数据

    // 使用 writeData 写入数据
    storageLayer.writeData(offset, writeData, std::strlen(writeData));

    // 测试读取数据
    std::string readData = storageLayer.readData(offset);

    // 输出读取的数据
    std::cout << "Read Data: " << readData << std::endl;

    std::cout << "Test passed!" << std::endl;
}

int main()
{
    testStorageLayer();
    return 0;
}
