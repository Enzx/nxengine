#pragma once

#include <chrono>
#include <source_location>

#include "base/nx_pch.h"

namespace nx::logs
{
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
        static std::string get_log_level_color(const log_level& level);

        logger() = default;
        ~logger() = default;
    };

 
}

   // Log macros
#if defined(_DEBUG) || defined(NX_DEBUG) || defined(NX_RELEASE)
#define NX_LOG_TRACE(message)    nx::logs::logger::log_message(nx::logs::log_level::trace, message)
#define NX_LOG_DEBUG(message)    nx::logs::logger::log_message(nx::logs::log_level::debug, message)
#define NX_LOG_INFO(message)     nx::logs::logger::log_message(nx::logs::log_level::info, message)
#define NX_LOG_WARNING(message)  nx::logs::logger::log_message(nx::logs::log_level::warning, message)
#define NX_LOG_ERROR(message)    nx::logs::logger::log_message(nx::logs::log_level::error, message)
#define NX_LOG_CRITICAL(message) nx::logs::logger::log_message(nx::logs::log_level::critical, message)
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
#define NX_LOG_TRACEF(fmt, ...)    nx::logs::logger::log_message(nx::logs::log_level::trace, std::format(fmt, __VA_ARGS__))
#define NX_LOG_DEBUGF(fmt, ...)    nx::logs::logger::log_message(nx::logs::log_level::debug, std::format(fmt, __VA_ARGS__))
#define NX_LOG_INFOF(fmt, ...)     nx::logs::logger::log_message(nx::logs::log_level::info, std::format(fmt, __VA_ARGS__))
#define NXLOG_WARNINGF(fmt, ...)   nx::logs::logger::log_message(nx::logs::log_level::warning, std::format(fmt, __VA_ARGS__))
#define NX_LOG_ERRORF(fmt, ...)    nx::logs::logger::log_message(nx::logs::log_level::error, std::format(fmt, __VA_ARGS__))
#define NX_LOG_CRITICALF(fmt, ...) nx::logs::logger::log_message(nx::logs::log_level::critical, std::format(fmt, __VA_ARGS__))
#else
#define NX_LOG_TRACEF(fmt, ...)
#define NX_LOG_DEBUGF(fmt, ...)
#define NX_LOG_INFOF(fmt, ...)
#define NX_LOG_WARNINGF(fmt, ...)
#define NX_LOG_ERRORF(fmt, ...)
#define NX_LOG_CRITICALF(fmt, ...)
#endif

    //Debug breakpoint
#define NX_DEBUG_BREAKPOINT() __debugbreak()

    //Debug Pause
#define DEBUG_PAUSE() std::cin.get()

    //Debug Assert
#define NX_DEBUG_ASSERT(condition, message) \
if (!(condition)) \
{ \
NX_LOG_ERROR(message); \
NX_DEBUG_BREAKPOINT(); \
}

    // Debug Assert with std::format
#define NX_DEBUG_ASSERTF(condition, fmt, ...) \
if (!(condition)) \
{ \
NX_LOG_ERRORF(fmt, __VA_ARGS__); \
DEBUG_BREAKPOINT(); \
}

    // OpenGL error check
#ifdef DEBUG
#define GL_CHECK_ERROR() \
do { \
GLenum err = glGetError(); \
while (err != GL_NO_ERROR) { \
NX_LOG_ERRORF("OpenGL Error: {:x}", err); \
std::cin.get(); \
} \
} while (0)
#else
#define GL_CHECK_ERROR() ((void)0)
#endif
