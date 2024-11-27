#include <sstream>
#include <string>
#include <cstring>

enum class DataType
{
    INT,
    FLOAT,
    DOUBLE,
    BOOL,
    STRING,
    UNKNOWN
};

class Serializer
{
public:
    template <typename T>
    static DataType getTypeEnum()
    {
        if (typeid(T) == typeid(int))
            return DataType::INT;
        if (typeid(T) == typeid(float))
            return DataType::FLOAT;
        if (typeid(T) == typeid(double))
            return DataType::DOUBLE;
        if (typeid(T) == typeid(bool))
            return DataType::BOOL;
        if (typeid(T) == typeid(std::string))
            return DataType::STRING;
        return DataType::UNKNOWN;
    }
    // 序列化任意数据（结构体/基础类型）
    template <typename T>
    static std::string serialize(const T &value);
    // 反序列化任意数据
    // template <typename T>
    static void *deserialize(const std::string &serialized_value, DataType type);

    // // 序列化字符串
    // static std::string serializeString(const std::string& value);

    // // 反序列化字符串
    // static std::string deserializeString(const std::string& data) ;
};
