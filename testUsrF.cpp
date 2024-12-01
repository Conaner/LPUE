#include <iostream>
#include "code/UserInterface.h"

// int main() {
//     UserInterface ui;

//     // 测试 put 和 get 功能
//     std::cout << "Testing put and get:" << std::endl;
//     ui.put(1, 42);          // 存储 int 类型
//     ui.put(2, 3.14f);       // 存储 float 类型
//     ui.put(3, "Hello");     // 存储 string 类型

//     ui.get(1);  // 获取 int 类型值
//     ui.get(2);  // 获取 float 类型值
//     ui.get(3);  // 获取 string 类型值
//     ui.get(4);  // 获取不存在的key

//     // 测试 del 功能
//     std::cout << "\nTesting del:" << std::endl;
//     ui.del(2);  // 删除 key = 2
//     ui.get(2);  // 尝试获取已删除的key
//     ui.del(4);  // 尝试删除不存在的key

//     return 0;
// }

#include <thread>
#include <vector>
#include <random>
#include <chrono>

void test_put(UserInterface &ui, int thread_id, int num_operations)
{
    for (int i = 0; i < num_operations; ++i)
    {
        int key = thread_id * 1000 + i; // 每个线程使用不同的 key 范围
        int value = key * 10;
        ui.put(key, value);
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 模拟延迟
    }
}

void test_get(UserInterface &ui, int thread_id, int num_operations)
{
    for (int i = 0; i < num_operations; ++i)
    {
        int key = thread_id * 1000 + i; // 每个线程访问同一范围的 key
        ui.get(key);
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 模拟延迟
    }
}

void test_del(UserInterface &ui, int thread_id, int num_operations)
{
    for (int i = 0; i < num_operations; ++i)
    {
        int key = thread_id * 1000 + i; // 每个线程访问同一范围的 key
        ui.del(key);
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 模拟延迟
    }
}

int main()
{
    UserInterface ui; // 创建用户接口实例

    const int num_threads = 4;         // 并发线程数量
    const int num_operations = 100;   // 每个线程执行的操作数

    std::vector<std::thread> threads;

    // 启动多个线程执行 put 操作
    for (int i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(test_put, std::ref(ui), i, num_operations);
    }

    // 等待所有 put 线程完成
    for (auto &t : threads)
    {
        t.join();
    }

    threads.clear(); // 清空线程列表

    // 启动多个线程执行 get 操作
    for (int i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(test_get, std::ref(ui), i, num_operations);
    }

    // 等待所有 get 线程完成
    for (auto &t : threads)
    {
        t.join();
    }

    threads.clear(); // 清空线程列表

    // 启动多个线程执行 del 操作
    for (int i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(test_del, std::ref(ui), i, num_operations);
    }

    // 等待所有 del 线程完成
    for (auto &t : threads)
    {
        t.join();
    }

    std::cout << "All operations completed!" << std::endl;

    return 0;
}
