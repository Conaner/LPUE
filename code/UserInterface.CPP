#include "UserInterface.h"

void UserInterface::put(const std::string &key, const std::string &value)
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

void UserInterface::get(const std::string &key)
{
    off_t offset = indexLayer.getOffset(key);
    if (offset != -1)
    {
        std::string value = bufferLayer.readValue(offset);
        std::cout << "GET successful: " << key << " -> " << value << std::endl;
    }
    else
    {
        std::cout << "Key not found!" << std::endl;
    }
}

void UserInterface::del(const std::string &key)
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
