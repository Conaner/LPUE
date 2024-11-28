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

    size_t delimiter_pos = value_serialized.find("_");
    std::string type_str = value_serialized.substr(0, delimiter_pos);
    // std::string data_str = value_serialized.substr(delimiter_pos + 1);

    DataType type = static_cast<DataType>(std::stoi(type_str));
    switch (type)
    {
    case DataType::INT:
    {
        int value = Serializer::deserialize<int>(value_serialized);
        std::cout << "GET successful: " << key << " -> " << value << std::endl;
        break;
    }
    case DataType::FLOAT:
    {
        float value = Serializer::deserialize<float>(value_serialized);
        std::cout << "GET successful: " << key << " -> " << value << std::endl;
        break;
    }
    case DataType::DOUBLE:
    {
        double value = Serializer::deserialize<double>(value_serialized);
        std::cout << "GET successful: " << key << " -> " << value << std::endl;
        break;
    }
    case DataType::BOOL:
    {
        bool value = Serializer::deserialize<bool>(value_serialized);
        std::cout << "GET successful: " << key << " -> " << (value ? "true" : "false") << std::endl;
        break;
    }
    case DataType::STRING:
    {
        std::string value = Serializer::deserialize<std::string>(value_serialized);
        std::cout << "GET successful: " << key << " -> " << value << std::endl;
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
