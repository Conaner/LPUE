// #include "code/UserInterface.h"

// #include <thread>
// #include <queue>
// #include <mutex>
// #include <condition_variable>
// #include <random>
// #include <chrono>
// #include <fstream>
// #include <iostream>

// // 任务队列及同步工具
// std::queue<std::pair<std::int64_t, std::string>> task_queue;
// std::mutex queue_mutex;
// std::condition_variable queue_cond;

// // 日志记录
// std::ofstream log_file("stress_test.log");

// // 随机数据生成器
// std::pair<std::int64_t, std::string> generate_random_kv()
// {
//     static std::mt19937_64 rng(std::random_device{}());
//     static std::uniform_int_distribution<std::int64_t> key_dist(1, 1e10);
//     static std::uniform_int_distribution<char> char_dist('a', 'z');

//     std::int64_t key = key_dist(rng);
//     std::string value(10, ' ');
//     for (char &c : value)
//     {
//         c = char_dist(rng);
//     }
//     return {key, value};
// }

// // 日志记录函数
// void log_status(const std::string &message)
// {
//     auto now = std::chrono::system_clock::now();
//     auto time = std::chrono::system_clock::to_time_t(now);
//     log_file << std::ctime(&time) << ": " << message << std::endl;
// }

// // 生产者线程
// void producer(int num_operations)
// {
//     for (int i = 0; i < num_operations; ++i)
//     {
//         auto kv = generate_random_kv();
//         {
//             std::lock_guard<std::mutex> lock(queue_mutex);
//             task_queue.push(kv);
//         }
//         queue_cond.notify_one(); // 唤醒消费者
//     }
// }

// // 消费者线程
// void consumer(UserInterface &ui, bool &running)
// {
//     while (running || !task_queue.empty())
//     {
//         std::pair<std::int64_t, std::string> task;
//         {
//             std::unique_lock<std::mutex> lock(queue_mutex);
//             queue_cond.wait(lock, [] { return !task_queue.empty(); }); // 等待任务
//             if (task_queue.empty())
//                 continue;
//             task = task_queue.front();
//             task_queue.pop();
//         }
//         // 执行 PUT、GET 和 DELETE 操作
//         ui.put(task.first, task.second);
//         ui.get(task.first);
//         ui.del(task.first);
//     }
// }

// // 主函数
// int main()
// {
//     UserInterface ui; // 用户接口实例
//     const int num_producers = 4;
//     const int num_consumers = 4;
//     const int operations_per_producer = 2500000; // 每个生产者生成 250 万条数据

//     bool running = true; // 消费者运行状态
//     std::vector<std::thread> producers;
//     std::vector<std::thread> consumers;

//     log_status("Stress test started");

//     // 启动生产者线程
//     for (int i = 0; i < num_producers; ++i)
//     {
//         producers.emplace_back(producer, operations_per_producer);
//     }

//     // 启动消费者线程
//     for (int i = 0; i < num_consumers; ++i)
//     {
//         consumers.emplace_back(consumer, std::ref(ui), std::ref(running));
//     }

//     // 等待生产者完成
//     for (auto &p : producers)
//     {
//         p.join();
//     }

//     running = false; // 停止消费者
//     queue_cond.notify_all();

//     // 等待消费者完成
//     for (auto &c : consumers)
//     {
//         c.join();
//     }

//     log_status("Stress test completed");
//     log_file.close();

//     std::cout << "Stress test completed. Logs written to stress_test.log" << std::endl;
//     return 0;
// }
