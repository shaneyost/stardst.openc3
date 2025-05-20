#pragma once
#include <string>
#include <iostream>
#include <string_view>
#include <iomanip>

class Logger
{
public:
    enum class Level { WARN = 0, INFO = 1, DEBUG = 2 };

    /*
     *  Varadic template design for logger. All loggers use this
     * */
    template <typename... Args>
    static void log(Level lvl, std::string_view fle, std::string_view fnc, int lne, 
                    const std::string& fmt, Args&&... args)
    {
        if (lvl > get_log_lvl())
        {
            return;
        }

        // account for proper spacing of a level, prettier prints
        std::string spacing = (lvl == Level::DEBUG) ? "" : " ";
        std::cout << "[" << lvl_to_str(lvl) << "] " << spacing
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

    /*
     *  Logs buffers of uint8_t types only
     *  TODO:   Later decide if we want to add a template here for other types
     * */
    static void buf(Level lvl, std::string_view fle, std::string_view fnc, int lne, 
                    const uint8_t* data, size_t total_len, size_t len_to_print)
    {
        if (lvl > get_log_lvl())
        {
            return;
        }

        // account for proper spacing of a level, prettier prints
        std::string spacing = (lvl == Level::DEBUG) ? "" : " ";
        std::cout << "[" << lvl_to_str(lvl) << "] " << spacing
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

    /*
     *  Overrides buf in order to support both vectors and uint8_t
     * */
    static void buf(Level lvl, std::string_view fle, std::string_view fnc, int lne, 
                    const std::vector<uint8_t>& data, size_t len_to_print)
    {
        buf(lvl, fle, fnc, lne, data.data(), data.size(), len_to_print);
    }

private:
    inline static constexpr const char* ENV_VAR = "LOG_LVL";

    /*
     *  Retrieves the environment variable, returns level via mini lambda
     * */
    static Level get_log_lvl()
    {
        static Level cached_level = [] {

            const char* env = std::getenv(ENV_VAR);
            if (!env) return Level::WARN;

            //  returns 0 if env is not a valid number (i.e if atoi fails)
            int level_int = std::atoi(env);
            if (level_int < 0 || level_int > static_cast<int>(Level::DEBUG)) {
                return Level::WARN;
            }

            return static_cast<Level>(level_int);
        }();
        return cached_level;
    }

    /*
     *  Converts a level string into a Level then returns it
     * */
    static const char* lvl_to_str(Level lvl)
    {
        switch (lvl)
        {
            case Level::DEBUG: return "DEBUG";
            case Level::INFO:  return "INFO";
            case Level::WARN:  return "WARN";
            default: return "WARN";
        }
    }

    /*
     *  Prevent the full path getting printed, only care about file name
     * */
    static std::string_view base(std::string_view path)
    {
        size_t pos = path.find_last_of("/\\");
        return (pos == std::string_view::npos) ? path : path.substr(pos + 1);
    }
};

/*
 *  Usage:
 *  LOG(Logger::Level::DEBUG, "Telemetry reading: %d", value);
 *  LOG_BUFFER(Logger::Level::DEBUG, buffer, total_len, 32);
 *  LOG_VECTOR(Logger::Level::DEBUG, vec, 64);
 * */
#define LOG(lvl, ...)               Logger::log(lvl, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOG_BUFFER(lvl, d, tl, pl)  Logger::buf(lvl, __FILE__, __func__, __LINE__, d, tl, pl)
#define LOG_VECTOR(lvl, d, pl)      Logger::buf(lvl, __FILE__, __func__, __LINE__, d, pl)

