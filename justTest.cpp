#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>
#include <stdexcept>

template <typename T>
class Serializer
{
public:
    // 序列化，将类型和数据拼接成 "类型_数据" 形式
    static std::string serialize(const T &value)
    {
        std::stringstream ss;
        ss << typeToString(value) << "_" << value; // 拼接类型和值
        return ss.str();
    }

    // 反序列化，将 "类型_数据" 转换回原始数据
    // static T deserialize(const std::string &serialized_value)
    // {
    //     std::string type;
    //     std::string value_str;

    //     // 拆分字符串，查找 "_" 分隔符
    //     size_t separator_pos = serialized_value.find('_');
    //     if (separator_pos == std::string::npos)
    //     {
    //         throw std::invalid_argument("Invalid serialized string format.");
    //     }

    //     type = serialized_value.substr(0, separator_pos);
    //     value_str = serialized_value.substr(separator_pos + 1);
        
    //     std::cout << "type:" << type <<" "<<   std::endl;
        
    //     // 根据类型字符串反序列化
    //     if (type == "int")
    //     {
    //         return value_str;
    //         // std::cout << "int" << std::endl;
    //         // return std::stoi(value_str);
    //     //     return stringToValue<int>(value_str);
    //     }
    //     else if (type == "float")
    //     {
    //         return value_str;
    //         // return std::stof(value_str);
    //         //  std::cout << "float" << std::endl;
    //         // return stringToValue<float>(value_str);
    //     }
    //     else if (type == "string")
    //     {
    //         std::cout << "string" << std::endl;
    //         return value_str;  // 字符串类型直接返回
    //     }
    //     else
    //     {
    //         throw std::invalid_argument("Unknown type in serialized string.");
    //     }
    //     return NULL;
    // }

private:
    // 类型转换为字符串
    static std::string typeToString(const T &value)
    {
        if constexpr (std::is_integral<T>::value)
        {
            return "int";
        }
        else if constexpr (std::is_floating_point<T>::value)
        {
            return "float";
        }
        else if constexpr (std::is_same<T, std::string>::value)
        {
            return "string";
        }
        else
        {
            return "unknown";
        }
    }

    // 将字符串转换为相应类型的值
    template <typename U>
    static U stringToValue(const std::string &value_str)
    {
        std::istringstream iss(value_str);
        U value;
        iss >> value;

        if (iss.fail())
        {
            throw std::invalid_argument("Failed to convert string to value.");
        }

        return value;
    }
};

int main()
{
    int a = 5;
    float b = 3.14;
    std::string c = "hello";

    // 序列化
    std::string serialized_a = Serializer<int>::serialize(a);
    std::string serialized_b = Serializer<float>::serialize(b);
    std::string serialized_c = Serializer<std::string>::serialize(c);

    // 输出序列化后的结果
    std::cout << "Serialized int: " << serialized_a << std::endl;
    std::cout << "Serialized float: " << serialized_b << std::endl;
    std::cout << "Serialized string: " << serialized_c << std::endl;

    // 反序列化
    // int deserialized_a = Serializer<int>::deserialize(serialized_a);
    // float deserialized_b = Serializer<float>::deserialize(serialized_b);
    // std::string deserialized_c = Serializer<std::string>::deserialize(serialized_c);

    // 输出反序列化后的结果
    // std::cout << "Deserialized int: " << deserialized_a << std::endl;
    // std::cout << "Deserialized float: " << deserialized_b << std::endl;
    // std::cout << "Deserialized string: " << deserialized_c << std::endl;

    return 0;
}
