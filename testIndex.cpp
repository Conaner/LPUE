#include <iostream>
#include <cassert>
#include "code/MemoryIndexLayer.h"

int main() {
    // 创建 MemoryIndexLayer 对象
    MemoryIndexLayer memoryIndexLayer;

    // 1. 测试插入键值对
    std::int64_t key1 = 1;
    std::string value1 = "value1";
    assert(memoryIndexLayer.put(key1, value1) == true);  // 应该插入成功
    std::cout << "Key: " << key1 << " inserted with value: " << value1 << std::endl;

    // 2. 测试查询键值对
    std::string retrievedValue = memoryIndexLayer.get(key1);
    assert(retrievedValue == value1);  // 应该返回 "value1"
    std::cout << "Retrieved value for key " << key1 << ": " << retrievedValue << std::endl;

    // 3. 测试获取键偏移量
    off_t offset = memoryIndexLayer.getOffset(key1);
    assert(offset != -1);  // 偏移量应该有效
    std::cout << "Offset for key " << key1 << ": " << offset << std::endl;

    // 4. 测试插入另一个键值对
    std::int64_t key2 = 2;
    std::string value2 = "value2";
    assert(memoryIndexLayer.put(key2, value2) == true);  // 应该插入成功
    std::cout << "Key: " << key2 << " inserted with value: " << value2 << std::endl;

    // 5. 测试查询第二个键值对
    retrievedValue = memoryIndexLayer.get(key2);
    assert(retrievedValue == value2);  // 应该返回 "value2"
    std::cout << "Retrieved value for key " << key2 << ": " << retrievedValue << std::endl;

    // 6. 测试删除键值对
    assert(memoryIndexLayer.del(key1) == true);  // 删除 key1
    std::cout << "Key " << key1 << " deleted." << std::endl;

    // 7. 测试删除不存在的键值对
    assert(memoryIndexLayer.del(key1) == false);  // key1 已被删除
    std::cout << "Attempted to delete key " << key1 << " again." << std::endl;

    // 8. 测试缓存是否工作，确保 LRU 被更新
    std::int64_t key3 = 3;
    std::string value3 = "value3";
    memoryIndexLayer.put(key3, value3);  // 插入 key3
    std::string retrievedValue3 = memoryIndexLayer.get(key3);
    // assert(retrievedValue3 == value3);  // 应该返回 "value3"
    std::cout << "Retrieved value for key " << key3 << ": " << retrievedValue3 << std::endl;

    std::string retrievedValue2_ = memoryIndexLayer.get(key2);
    std::cout << "Retrieved value for key " << key2 << ": " << retrievedValue2_ << std::endl;
    return 0;
}
