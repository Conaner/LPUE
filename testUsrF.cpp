#include <iostream>
#include "code/UserInterface.h"

int main() {
    UserInterface ui;

    // 测试 put 和 get 功能
    std::cout << "Testing put and get:" << std::endl;
    ui.put(1, 42);          // 存储 int 类型
    ui.put(2, 3.14f);       // 存储 float 类型
    ui.put(3, "Hello");     // 存储 string 类型

    ui.get(1);  // 获取 int 类型值
    ui.get(2);  // 获取 float 类型值
    ui.get(3);  // 获取 string 类型值
    ui.get(4);  // 获取不存在的key

    // 测试 del 功能
    std::cout << "\nTesting del:" << std::endl;
    ui.del(2);  // 删除 key = 2
    ui.get(2);  // 尝试获取已删除的key
    ui.del(4);  // 尝试删除不存在的key

    return 0;
}

