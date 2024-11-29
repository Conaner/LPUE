// #include <string>
// #include <type_traits>
// #include <sstream>


// template <typename T>
// class Serializer
// {
// public:
//     // 序列化，将类型和数据拼接成 "类型_数据" 形式
//     // template <typename T>
//     static std::string serialize(const T &value)
//     {
//         std::stringstream ss;
//         ss << typeToString(value) << "_" << value; // 拼接类型和值
//         return ss.str();
//     }

//     // template <typename T>
//     // static DataType getTypeEnum();

//     // 反序列化，将 "类型_数据" 转换回原始数据
//     // template <typename T>
//     // static T deserialize(const std::string &serialized_value){
//     //     std::string type;
//     //     std::string value_str;
//     //     size_t separator_pos = serialized_value.find('_');
//     //     if (separator_pos == std::string::npos)
//     //     {
//     //         throw std::invalid_argument("Invalid serialized string format.");
//     //     }
//     //     type = serialized_value.substr(0, separator_pos);
//     //     value_str = serialized_value.substr(separator_pos + 1);
//     //     if (type == "int")
//     //     {
//     //         return stringToValue<int>(value_str);
//     //     }
//     //     else if (type == "float")
//     //     {
//     //         return stringToValue<float>(value_str);
//     //     }
//     //     else if (type == "string")
//     //     {
//     //         return value_str;  // 字符串类型直接返回
//     //     }
//     //     else
//     //     {
//     //         throw std::invalid_argument("Unknown type in serialized string.");
//     //     }
//     // }

// private:
//     // 类型转换为字符串
//     static std::string typeToString(const T &value)
//     {
//         if constexpr (std::is_integral<T>::value)
//         {
//             (void)sizeof(value);  // 消除编译报错 “变量未使用”
//             return "int";
//         }
//         else if constexpr (std::is_floating_point<T>::value)
//         {
//             (void)sizeof(value); 
//             return "float";
//         }
//         else if constexpr (std::is_same<T, std::string>::value)
//         {
//             (void)sizeof(value); 
//             return "string";
//         }
//         else
//         {
//             (void)sizeof(value); 
//             return "unknown";
//         }
//     }
//     // template <typename U>
//     // static U stringToValue(const std::string &value_str)
//     // {
//     //     std::istringstream iss(value_str);
//     //     U value;
//     //     iss >> value;

//     //     if (iss.fail())
//     //     {
//     //         throw std::invalid_argument("Failed to convert string to value.");
//     //     }

//     //     return value;
//     // }
// };
