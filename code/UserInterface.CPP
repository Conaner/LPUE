#include "UserInterface.h"
#include "Serializer.h"

template <typename T>

void UserInterface::put(const std::int64_t &key, const T &value)
{
    value_serialized = Serializer::serialize(value); // value变成了string
    bool success = indexLayer.put(key, value_serialized);
    if (success)
    {
        std::cout << "PUT successful: " << key << " -> " << value << std::endl;
    }
    else
    {
        std::cout << "PUT failed: key already exists" << std::endl;
    }
}

void UserInterface::get(const std::int64_t &key)
{
    std::string value_serialized = indexLayer.get(key); 
    if (value_serialized.empty())
    {
        std::cout << "Key not found!" << std::endl;
        return;
    }
    // 提取类型信息
    std::string type_info_line;
    std::stringstream ss(value_serialized);
    std::getline(ss, type_info_line); // 提取类型信息行

    // string变回原来的类型
    DataType type = static_cast<DataType>(std::stoi(type_info_line));

    switch (type)
    {
    case DataType::INT:
    {
        int *value = static_cast<int *>(Serializer::deserialize(value_serialized, type));
        std::cout << "GET successful: " << key << " -> " << *value << std::endl;
        delete value;
        break;
    }
    case DataType::FLOAT:
    {
        float *value = static_cast<float *>(Serializer::deserialize(value_serialized, type));
        std::cout << "GET successful: " << key << " -> " << *value << std::endl;
        delete value;
        break;
    }
    case DataType::DOUBLE:
    {
        double *value = static_cast<double *>(Serializer::deserialize(value_serialized, type));
        std::cout << "GET successful: " << key << " -> " << *value << std::endl;
        delete value;
        break;
    }
    case DataType::BOOL:
    {
        bool *value = static_cast<bool *>(Serializer::deserialize(value_serialized, type));
        std::cout << "GET successful: " << key << " -> " << *value << std::endl;
        delete value;
        break;
    }
    case DataType::STRING:
    {
        std::string *value = static_cast<std::string *>(Serializer::deserialize(value_serialized, type));
        std::cout << "GET successful: " << key << " -> " << *value << std::endl;
        delete value;
        break;
    }
    default:
        std::cout << "Unsupported type!" << std::endl;
        break;
    }
}

void UserInterface::del(const std::int64_t &key)
{
    bool success = indexLayer.del(key);
    if (success)
    {
        std::cout << "DEL successful: " << key << std::endl;
    }
    else
    {
        std::cout << "DEL failed: key not found" << std::endl;
    }
}
