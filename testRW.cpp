#include <iostream>
#include "code/ReadWriteBuffer.h"
#include "code/StorageLayer.h"

int main() {
    try {
        ReadWriteBuffer rwBuffer;

        // 测试写 Key
        std::int64_t key1 = 123456;
        off_t keyOffset = rwBuffer.writeKey(key1);
        std::cout << "Key written at offset: " << keyOffset << std::endl;

        // 测试写 Value
        std::string value1 = "This is a test value";
        off_t valueOffset = rwBuffer.writeValue(value1);
        std::cout << "Value written at offset: " << valueOffset << std::endl;

        std::string value2 = "This is the second test value";
        off_t valueOffset2 = rwBuffer.writeValue(value2);
        std::cout << "Value written at offset: " << valueOffset2 << std::endl;

        // 刷新缓冲区到磁盘
        rwBuffer.flushKeyBufferToDisk();
        rwBuffer.flushValueBufferToDisk();

        // 测试读取 Value
        std::string readValue = rwBuffer.readValue(valueOffset2);
        std::cout << "Read Value: " << readValue << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
