#include "Serializer.h"

// 序列化任意数据（结构体/基础类型）
template <typename T>
static std::string serialize(const T &value)
{
    std::stringstream ss;
    DataType type = getTypeEnum<T>();
    ss << static_cast<int>(type) << "\n"; // 存储类型信息
    ss << value;                          // 存储数据
    return ss.str();
}

// 反序列化任意数据
static void* deserialize(const std::string& serialized_value, DataType type)
{
    std::stringstream ss(serialized_value);
    ss.ignore(); // 跳过类型信息行

    switch (type)
    {
    case DataType::INT:
    {
        int *value = new int;
        ss >> *value;
        return value;
    }
    case DataType::FLOAT:
    {
        float *value = new float;
        ss >> *value;
        return value;
    }
    case DataType::DOUBLE:
    {
        double *value = new double;
        ss >> *value;
        return value;
    }
    case DataType::BOOL:
    {
        bool *value = new bool;
        ss >> *value;
        return value;
    }
    case DataType::STRING:
    {
        std::string *value = new std::string;
        ss >> *value;
        return value;
    }
    default:
        return nullptr;
    }
}

// 序列化字符串
// static std::string serializeString(const std::string &value)
// {
//     return value; // 字符串本身可以直接作为二进制存储
// }

// // 反序列化字符串
// static std::string deserializeString(const std::string &data)
// {
//     return data; // 直接返回字符串
// }
