#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdio>

class Logger
{
public:
    static constexpr size_t DEFAULT_DUMP_LEN = 12;

    // defining template here for now, think this is ok
    template <typename... Args>
    static void info(const std::string& format, Args... args)
    {
        std::cout << "[INFO] ";
        if constexpr (sizeof...(args) == 0)
        {
            std::cout << format << std::endl;
        }
        else
        {
            std::printf(format.c_str(), args...);
            std::printf("\n");
        }
    }

    static void dump(const uint8_t* data, size_t length, size_t maxLen = DEFAULT_DUMP_LEN);
    static void dump(const std::vector<uint8_t>& data, size_t maxLen = DEFAULT_DUMP_LEN);
};
