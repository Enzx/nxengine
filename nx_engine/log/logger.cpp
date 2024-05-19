#include "logger.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

log_level logger::log_level_threshold = log_level::trace;

std::string logger::get_current_time()
{
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm{};
#ifdef _WIN32
    if (localtime_s(&now_tm, &now_time_t) != 0) {
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

std::string logger::get_log_level_text(const log_level& level)
{
    switch (level)
    {
    case log_level::trace: return "TRACE";
    case log_level::debug: return "DEBUG";
    case log_level::info: return "INFO";
    case log_level::warning: return "WARNING";
    case log_level::error: return "ERROR";
    case log_level::critical: return "CRITICAL";
    }
    return "UNKNOWN";
}

void logger::log_message(const log_level& level, const std::string& message, const std::source_location& location)
{
    if (level < log_level_threshold) return;
    const auto level_text = get_log_level_text(level);
    std::ostringstream oss;
    oss << "[" << get_current_time() << "]"
        << "[" << level_text << "]"
        << location.function_name() << " [" << location.file_name() << ":" << location.line() << "]: " << message;
    std::cout << oss.str() << '\n';
}
