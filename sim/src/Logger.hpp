#pragma once
#include <string>
#include <iostream>
#include <string_view>
#include <iomanip>

class Logger
{
public:
    /*
     *  INFO:
     *
     *  Varadic template design for logger. All loggers use this
     * */
    template <typename... Args>
    static void log(std::string_view lvl, std::string_view fle, std::string_view fnc, int lne, 
                    const std::string& fmt, Args&&... args)
    {
        Level level = str_to_lvl(lvl);

        if (level > get_log_lvl())
        {
            return;
        }

        // account for proper spacing of a level, prettier prints
        std::string spacing = (level == Level::DEBUG) ? "" : " ";

        std::cout << "[" << lvl << "] " << spacing
                  << "[" << base(fle) << ":" << fnc << " (" << lne << ")] ";

        if constexpr (sizeof...(args) == 0)
        {
            std::cout << fmt << std::endl;
        }
        else
        {
            std::printf(fmt.c_str(), args...);
            std::printf("\n");
        }
    }

    static void buf(std::string_view lvl, std::string_view fle, std::string_view fnc, int lne, 
                    const uint8_t* data, size_t total_len, size_t len_to_print)
    {
        Level level = str_to_lvl(lvl);

        if (level > get_log_lvl())
        {
            return;
        }

        // account for proper spacing of a level, prettier prints
        std::string spacing = (level == Level::DEBUG) ? "" : " ";

        std::cout << "[" << lvl << "] " << spacing
                  << "[" << base(fle) << ":" << fnc << " (" << lne << ")] ";

        size_t safe_len_to_print = (total_len < len_to_print) ? total_len : len_to_print;
        for (size_t i = 0; i < safe_len_to_print; i++)
        {
             std::cout << std::hex << std::setw(2) << std::setfill('0')
                       << static_cast<int>(data[i]) << " ";
        }

        if (total_len >= len_to_print)
        {
            std::cout << "... (" << total_len << " bytes total)";
        }
        std::cout << std::dec << std::endl;
    }

    static void buf(std::string_view lvl, std::string_view fle, std::string_view fnc, int lne, 
                    const std::vector<uint8_t>& data, size_t len_to_print)
    {
        buf(lvl, fle, fnc, lne, data.data(), data.size(), len_to_print);
    }

private:
    /*
     *  INFO:
     *
     *  Level   - An enumeration of numerical values representing a logging level
     *  ENV_VAR - Compile-time constant pointer to env variable for configuring logging level
     * */
    enum class Level { WARN = 0, INFO = 1, DEBUG = 2 };
    inline static constexpr const char* ENV_VAR = "LOG_LVL";

    /*
     *  INFO:
     *
     *  Retrieves the environment variable, returns level via mini lambda
     * */
    static Level get_log_lvl()
    {
        // mini lambda, caches (evaluates once design)
        static Level cached_level = [] {
            const char * env = std::getenv(ENV_VAR);
            if (!env) return Level::WARN;

            std::string_view level{env};
            if (!level.compare("DEBUG")) return Level::DEBUG;
            if (!level.compare("INFO")) return Level::INFO;

            return Level::WARN;
        }();
        return cached_level;
    }

    /*
     *  INFO:
     *
     *  Converts a level string into a Level then returns it
     *
     * */
    static Level str_to_lvl(std::string_view lvl)
    {
        if (!lvl.compare("DEBUG")) return Level::DEBUG;
        if (!lvl.compare("INFO")) return Level::INFO;
        return Level::WARN;
    }

    /*
     *  INFO:
     *
     *  Prevent the full path getting printed, only care about file name
     *
     *  WARN:
     *
     *  We're safe here as long as we immediately use the return value
     * */
    static std::string_view base(std::string_view path)
    {
        size_t pos = path.find_last_of("/\\");
        return (pos == std::string_view::npos) ? path : path.substr(pos + 1);
    }
};

#define LOG_WARN(...) Logger::log("WARN", __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) Logger::log("INFO", __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) Logger::log("DEBUG", __FILE__, __func__, __LINE__, __VA_ARGS__)

#define LOG_BUFFER_WARN(d, tl, pl) Logger::buf("WARN", __FILE__, __func__, __LINE__, d, tl, pl)
#define LOG_BUFFER_INFO(d, tl, pl) Logger::buf("INFO", __FILE__, __func__, __LINE__, d, tl, pl)
#define LOG_BUFFER_DEBUG(d, tl, pl) Logger::buf("DEBUG", __FILE__, __func__, __LINE__, d, tl, pl)

#define LOG_VECTOR_WARN(d, pl) Logger::buf("WARN", __FILE__, __func__, __LINE__, d, pl)
#define LOG_VECTOR_INFO(d, pl) Logger::buf("INFO", __FILE__, __func__, __LINE__, d, pl)
#define LOG_VECTOR_DEBUG(d, pl) Logger::buf("DEBUG", __FILE__, __func__, __LINE__, d, pl)
