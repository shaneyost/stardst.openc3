#include "Logger.hpp"

void Logger::dump(const uint8_t* data, size_t length, size_t maxLen)
{
    std::cout << "[DUMP] ";
    size_t toPrint = (length < maxLen) ? length : maxLen;
    for (size_t i = 0; i < toPrint; ++i)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>(data[i]) << " ";
    }
    if (length > maxLen)
    {
        std::cout << "... (" << length << " bytes total)";
    }
    std::cout << std::dec << std::endl;
}

void Logger::dump(const std::vector<uint8_t>& data, size_t maxLen)
{
    dump(data.data(), data.size(), maxLen);
}

