#include <iostream>
#include <string>
#include "MemoryIndexLayer.h" // 内存索引层

// template <typename T>

class UserInterface
{
public:
    // template <typename T>
    // void put(const std::int64_t &key, const T &value);
    void put(const std::int64_t &key, const int &value);
    void put(const std::int64_t &key, const float &value);
    void put(const std::int64_t &key, const std::string &value);
    // template <typename T>
    void get(const std::int64_t &key);

    void del(const std::int64_t &key);

private:
    MemoryIndexLayer indexLayer;
    // ReadWriteBuffer bufferLayer;
};
