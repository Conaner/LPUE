#include <iostream>
#include <string>
#include "MemoryIndexLayer.h"   // 内存索引层
#include "ReadWriteBuffer.h" // 读写缓冲层

class UserInterface
{
public:
    void put(const std::int64_t &key, const std::string &value);

    void get(const std::int64_t &key);

    void del(const std::int64_t &key);

private:
    MemoryIndexLayer indexLayer;
    // ReadWriteBuffer bufferLayer;
};
