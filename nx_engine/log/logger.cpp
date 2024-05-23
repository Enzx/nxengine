﻿#include "logger.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

logs::log_level logger::log_level_threshold = logs::log_level::trace;

std::string logger::get_current_time()
{
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm{};
#ifdef _WIN32
    if (localtime_s(&now_tm, &now_time_t) != 0)
    {
        return "Failed to get time";
    }
#else
    if (localtime_r(&now_time_t, &now_tm) == nullptr) {
        return "Failed to get time";
    }
#endif
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string logger::get_log_level_text(const logs::log_level& level)
{
    switch (level)
    {
    case logs::log_level::trace: return "TRACE";
    case logs::log_level::debug: return "DEBUG";
    case logs::log_level::info: return "INFO";
    case logs::log_level::warning: return "WARNING";
    case logs::log_level::error: return "ERROR";
    case logs::log_level::critical: return "CRITICAL";
    }
    return "UNKNOWN";
}

std::string logger::get_log_level_color(const logs::log_level& level)
{

    switch (level)
    {
    case logs::log_level::trace:
        return "\033[37m"; //white
    case logs::log_level::debug:
        return "\033[36m"; //cyan
    case logs::log_level::info:  
        return "\033[32m"; //green
    case logs::log_level::warning:
        return "\033[33m"; //yellow
    case logs::log_level::error:
        return "\033[31m"; //red
    case logs::log_level::critical:
        return "\033[35m"; //magenta
    }
    return "\033[0m"; //default color
}

void logger::log_message(const logs::log_level& level, const std::string& message, const std::source_location& location)
{
    if (level < log_level_threshold) return;
    const auto level_text = get_log_level_text(level);
    static const std::string default_color = "\033[0m";
    //set color based on log level
    std::string color = get_log_level_color(level);
    //Extract file name from path
    std::string file_name = location.file_name();
    size_t last_slash = file_name.find_last_of("/\\");
    if (last_slash != std::string::npos)
    {
        file_name = file_name.substr(last_slash + 1);
    }

    std::ostringstream oss;
    oss << "[" << get_current_time() << "]"
        << "[" << color << level_text << default_color << "]"
        << " [" << file_name << ":" << location.line() << "]: " << message;
    std::cout << oss.str() << '\n';
}
