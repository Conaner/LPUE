#include <string>
#include <type_traits>

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
    // 序列化，将类型和数据拼接成 "类型_数据" 形式
    template <typename T>
    static std::string serialize(const T &value);

    template <typename T>
    static DataType getTypeEnum();

    // 反序列化，将 "类型_数据" 转换回原始数据
    template <typename T>
    static T deserialize(const std::string &serialized_value);

    // // 序列化字符串
    // static std::string serializeString(const std::string& value);

    // // 反序列化字符串
    // static std::string deserializeString(const std::string& data) ;
};
