#include "UserInterface.h"

void UserInterface::put(const std::int64_t &key, const std::string &value)
{
    bool success = indexLayer.put(key, value);
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
    std::string value = indexLayer.get(key);
    if (value != "")
    {
        // std::string value = bufferLayer.readValue(offset);
        std::cout << "GET successful: " << key << " -> " << value << std::endl;
    }
    else
    {
        std::cout << "Key not found!" << std::endl;
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
