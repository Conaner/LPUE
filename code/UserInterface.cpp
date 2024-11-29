#include "UserInterface.h"
#include "Serializer.h"
#include <sstream>
// template <typename T>
// void UserInterface::put(const std::int64_t &key, const T &value)
// {
//     std::string value_serialized = Serializer::serialize(value); // value变成了string
//     bool success = indexLayer.put(key, value_serialized);
//     if (success)
//     {
//         std::cout << "PUT successful: " << key << " -> " << value << std::endl;
//     }
//     else
//     {
//         std::cout << "PUT failed: key already exists" << std::endl;
//     }
// }
void UserInterface::put(const std::int64_t &key, const int &value)
{
    std::stringstream ss;
    ss << "int_" << value;
    std::string value_serialized = ss.str();
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

void UserInterface::put(const std::int64_t &key, const float &value)
{
    std::stringstream ss;
    ss << "float_" << value;
    std::string value_serialized = ss.str();
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

void UserInterface::put(const std::int64_t &key, const std::string &value)
{
    std::stringstream ss;
    ss << "string_" << value;
    std::string value_serialized = ss.str();
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
    std::string data_str = value_serialized.substr(delimiter_pos + 1);

    if (type_str == "int")
    {
        std::cout << "Value: " << std::stoi(data_str) << std::endl;
    }
    else if (type_str == "float")
    {
        std::cout << "Value: " << std::stof(data_str) << std::endl;
    }
    else if (type_str == "string")
    {
        std::cout << "Value: " << data_str << std::endl;
    }
    else
    {
        std::cout << "Unsupported type!" << std::endl;
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
