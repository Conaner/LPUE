// #include <iostream>
// #include <string>
// #include <stdexcept>
// #include "code/Serializer.h"

// int main()
// {
//     try {
//         // 测试序列化
//         int num = 42;
//         std::string serialized_int = Serializer::serialize(num);
//         std::cout << "Serialized int: " << serialized_int << std::endl;

//         float f_val = 3.14;
//         std::string serialized_float = Serializer::serialize(f_val);
//         std::cout << "Serialized float: " << serialized_float << std::endl;

//         bool b_val = true;
//         std::string serialized_bool = Serializer::serialize(b_val);
//         std::cout << "Serialized bool: " << serialized_bool << std::endl;

//         // 测试反序列化
//         int deserialized_int = Serializer::deserialize<int>(serialized_int);
//         std::cout << "Deserialized int: " << deserialized_int << std::endl;

//         float deserialized_float = Serializer::deserialize<float>(serialized_float);
//         std::cout << "Deserialized float: " << deserialized_float << std::endl;

//         bool deserialized_bool = Serializer::deserialize<bool>(serialized_bool);
//         std::cout << "Deserialized bool: " << deserialized_bool << std::endl;

//     } catch (const std::exception &e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }

//     return 0;
// }
