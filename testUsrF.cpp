#include <iostream>
#include "code/UserInterface.h"
#include "code/Serializer.h"

// 创建一个 UserInterface 的实例
UserInterface ui;

void testPutAndGet()
{
    // 测试 PUT 操作和 GET 操作

    // 插入一个 int 类型的值
    int a = 42;
    ui.put(1, a);  // key = 1, value = 42

    // 插入一个 string 类型的值
    std::string str = "Hello, World!";
    ui.put(2, str);  // key = 2, value = "Hello, World!"

    // 获取并输出这两个值
    ui.get(1);  // 应该输出: GET successful: 1 -> 42
    ui.get(2);  // 应该输出: GET successful: 2 -> Hello, World!
}

void testDel()
{
    // 测试 DEL 操作

    // 删除 key = 1 的数据
    ui.del(1);  // 应该输出: DEL successful: 1

    // 尝试获取已删除的数据
    ui.get(1);  // 应该输出: Key not found!
}

int main()
{
    // 进行测试
    testPutAndGet();
    testDel();

    return 0;
}
