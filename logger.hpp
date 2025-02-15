// logger.hpp
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <mutex>
#include <cstdio>
#include <cstdarg>
#include <vector>
#include <atomic>

enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

class Logger {
public:
    static void setLevel(LogLevel level) {
        getAtomicLevel().store(level, std::memory_order_relaxed);
    }

    static LogLevel getLevel() {
        return getAtomicLevel().load(std::memory_order_relaxed);
    }

    static void log(const char* file, int line, LogLevel level, const char* fmt, ...) {
        if (level < getLevel()) return;

        std::lock_guard<std::mutex> lock(getMutex());
        std::string color = getColor(level);
        std::string reset = getReset();

        // 输出带颜色的级别和位置信息
        std::cerr << color << "[" << levelToString(level) << "]" << reset << " "
                  << file << ":" << line << " - ";

        // 处理格式化消息
        va_list args;
        va_start(args, fmt);
        int needed = vsnprintf(nullptr, 0, fmt, args);
        va_end(args);

        if (needed < 0) {
            std::cerr << "Formatting error in log message" << std::endl;
            return;
        }

        std::vector<char> buffer(needed + 1);
        va_start(args, fmt);
        vsnprintf(buffer.data(), buffer.size(), fmt, args);
        va_end(args);

        std::cerr << buffer.data() << std::endl;
    }

private:
    static std::atomic<LogLevel>& getAtomicLevel() {
        static std::atomic<LogLevel> level(DEBUG);
        return level;
    }

    static std::mutex& getMutex() {
        static std::mutex mtx;
        return mtx;
    }

    static std::string getColor(LogLevel level) {
        switch(level) {
            case DEBUG: return "\033[36m"; // 青色
            case INFO:  return "\033[32m"; // 绿色
            case WARN:  return "\033[33m"; // 黄色
            case ERROR: return "\033[31m"; // 红色
            case FATAL: return "\033[1;31m"; // 粗体红色
            default:    return "";
        }
    }

    static std::string getReset() {
        return "\033[0m";
    }

    static const char* levelToString(LogLevel level) {
        switch(level) {
            case DEBUG: return "DEBUG";
            case INFO:  return "INFO";
            case WARN:  return "WARN";
            case ERROR: return "ERROR";
            case FATAL: return "FATAL";
            default:    return "UNKNOWN";
        }
    }
};

#define LOG_DEBUG(...) Logger::log(__FILE__, __LINE__, DEBUG, __VA_ARGS__)
#define LOG_INFO(...)  Logger::log(__FILE__, __LINE__, INFO, __VA_ARGS__)
#define LOG_WARN(...)  Logger::log(__FILE__, __LINE__, WARN, __VA_ARGS__)
#define LOG_ERROR(...) Logger::log(__FILE__, __LINE__, ERROR, __VA_ARGS__)
#define LOG_FATAL(...) Logger::log(__FILE__, __LINE__, FATAL, __VA_ARGS__)

#endif // LOGGER_HPP
