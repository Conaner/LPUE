// #include "Serializer.h"
// // #include <sstream>
// // #include <stdexcept>
// // #include <iostream>

// // // 序列化，将类型和数据拼接成 "类型_数据" 形式
// // template <typename T>
// // std::string Serializer::serialize(const T &value)
// // {
// //     std::stringstream ss;
// //     DataType type = Serializer::getTypeEnum<T>();
// //     ss << static_cast<int>(type) << "_"; // 存储类型信息
// //     ss << value;                         // 存储数据
// //     return ss.str();
// // }

// // template <typename T>
// // DataType Serializer::getTypeEnum()
// // {
// //     if (std::is_same<T, int>::value)
// //         return DataType::INT;
// //     if (std::is_same<T, float>::value)
// //         return DataType::FLOAT;
// //     if (std::is_same<T, double>::value)
// //         return DataType::DOUBLE;
// //     if (std::is_same<T, bool>::value)
// //         return DataType::BOOL;
// //     if (std::is_same<T, std::string>::value)
// //         return DataType::STRING;
// //     return DataType::UNKNOWN;
// // }

// // // 反序列化，将 "类型_数据" 转换回原始数据
// // template <typename T>
// // T Serializer::deserialize(const std::string &serialized_value)
// // {
// //     // 从序列化字符串中提取类型和数据
// //     size_t delimiter_pos = serialized_value.find("_");
// //     std::string type_str = serialized_value.substr(0, delimiter_pos);
// //     std::string data_str = serialized_value.substr(delimiter_pos + 1);

// //     DataType type = static_cast<DataType>(std::stoi(type_str));
// //     std::cout << "Deserializing type: " << dataTypeToString(type) << std::endl;
// //     switch (type)
// //     {
// //     case DataType::INT:
// //         try {
// //             return static_cast<T>(std::stoi(data_str));  // 转换为 int
// //         } catch (const std::exception &e) {
// //             throw std::invalid_argument("Failed to deserialize INT: " + std::string(e.what()));
// //         }
// //     case DataType::FLOAT:
// //         try {
// //             return std::stof(data_str);  // 转换为 float
// //         } catch (const std::exception &e) {
// //             throw std::invalid_argument("Failed to deserialize FLOAT: " + std::string(e.what()));
// //         }
// //     case DataType::DOUBLE:
// //         try {
// //             return std::stod(data_str);  // 转换为 double
// //         } catch (const std::exception &e) {
// //             throw std::invalid_argument("Failed to deserialize DOUBLE: " + std::string(e.what()));
// //         }
// //     case DataType::BOOL:
// //         try {
// //             return std::stoi(data_str) != 0;  // 转换为 bool
// //         } catch (const std::exception &e) {
// //             throw std::invalid_argument("Failed to deserialize BOOL: " + std::string(e.what()));
// //         }
// //     case DataType::STRING:
// //         return data_str;
// //     default:
// //         throw std::invalid_argument("Unsupported type for deserialization");
// //     }
// // }

// // // // 显式实例化模板
// // template std::string Serializer::serialize<int>(const int& value);
// // template std::string Serializer::serialize<float>(const float& value);
// // template std::string Serializer::serialize<double>(const double& value);
// // template std::string Serializer::serialize<bool>(const bool& value);
// // template std::string Serializer::serialize<std::string>(const std::string& value);

// // template int Serializer::deserialize<int>(const std::string& serialized_value);
// // template float Serializer::deserialize<float>(const std::string& serialized_value);
// // template double Serializer::deserialize<double>(const std::string& serialized_value);
// // template bool Serializer::deserialize<bool>(const std::string& serialized_value);
// // template std::string Serializer::deserialize<std::string>(const std::string& serialized_value);
