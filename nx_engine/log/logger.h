#pragma once

#include <chrono>
#include <source_location>
#include <string>

enum class log_level
{
    trace,
    debug,
    info,
    warning,
    error,
    critical
};

class logger
{
public:
    logger(const logger& other) = delete;
    logger(logger&& other) noexcept = delete;
    logger& operator=(const logger& other) = delete;
    logger& operator=(logger&& other) noexcept = delete;

    static void log_message(const log_level& level, const std::string& message,
                            const std::source_location& location = std::source_location::current());

    static log_level log_level_threshold;

private:
    static std::string get_current_time();
    static std::string get_log_level_text(const log_level& level);

    logger() = default;
    ~logger() = default;
};

// Log macros
#if defined(_DEBUG) || defined(NX_DEBUG) || defined(NX_RELEASE)
#define LOG_TRACE(message)    logger::log_message(log_level::trace, message)
#define LOG_DEBUG(message)    logger::log_message(log_level::debug, message)
#define LOG_INFO(message)     logger::log_message(log_level::info, message)
#define LOG_WARNING(message)  logger::log_message(log_level::warning, message)
#define LOG_ERROR(message)    logger::log_message(log_level::error, message)
#define LOG_CRITICAL(message) logger::log_message(log_level::critical, message)
#else
#define LOG_TRACE(message)
#define LOG_DEBUG(message)
#define LOG_INFO(message)
#define LOG_WARNING(message)
#define LOG_ERROR(message)
#define LOG_CRITICAL(message)
#endif

// Log macros with std::format
#if defined(_DEBUG) || defined(NX_DEBUG) || defined(NX_RELEASE)
#define LOG_TRACEF(fmt, ...)    logger::log_message(log_level::trace, std::format(fmt, __VA_ARGS__))
#define LOG_DEBUGF(fmt, ...)    logger::log_message(log_level::debug, std::format(fmt, __VA_ARGS__))
#define LOG_INFOF(fmt, ...)     logger::log_message(log_level::info, std::format(fmt, __VA_ARGS__))
#define LOG_WARNINGF(fmt, ...)  logger::log_message(log_level::warning, std::format(fmt, __VA_ARGS__))
#define LOG_ERRORF(fmt, ...)    logger::log_message(log_level::error, std::format(fmt, __VA_ARGS__))
#define LOG_CRITICALF(fmt, ...) logger::log_message(log_level::critical, std::format(fmt, __VA_ARGS__))
#else
#define LOG_TRACEF(fmt, ...)
#define LOG_DEBUGF(fmt, ...)
#define LOG_INFOF(fmt, ...)
#define LOG_WARNINGF(fmt, ...)
#define LOG_ERRORF(fmt, ...)
#define LOG_CRITICALF(fmt, ...)
#endif
