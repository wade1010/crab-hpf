//
// Created by cepher on 5/7/23.
//

#include <cstring>
#include <cstdarg>
#include "Logger.h"

using namespace crab::logger;

Logger *Logger::m_instance = nullptr;

const char *Logger::s_level[5] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

Logger::Logger() : m_length(0), m_level(Level::DEBUG), m_max_bytes(0) {}

Logger::~Logger() {
    close();
}

Logger *Logger::instance() {
    if (m_instance == nullptr)
        m_instance = new Logger();
    return m_instance;
}

void Logger::open(const std::string &filename) {
    m_filename = filename;
    m_fout.open(m_filename.c_str(), std::ios::app);
    if (!m_fout.is_open())
        throw std::runtime_error("Could not open log file:" + m_filename);
    m_fout.seekp(0, std::ios::end);//将文件指针定位到文件末尾后
    m_length = m_fout.tellp();//获取当前文件指针的位置并将其赋值给m_length变量 ,注意文件指针的位置和文件长度并不完全一致
}

void Logger::close() {
    m_fout.close();
}

void Logger::log(Logger::Level level, const char *file, int line, const char *format, ...) {
    if (level < m_level)
        return;
    if (m_fout.fail())
        throw std::runtime_error("Could not open log file:" + m_filename);

    time_t ticks = time(nullptr);
    struct tm *ptm = localtime(&ticks);
    char timestamp[32];
    memset(timestamp, 0, sizeof(timestamp));
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", ptm);

    int len = 0;
    const char *fmt = "%s %s %s:%d ";
    len = snprintf(nullptr, 0, fmt, timestamp, s_level[int(level)], file, line);
    if (len > 0) {
        char *buffer = new char[len + 1];
        snprintf(buffer, len + 1, fmt, timestamp, s_level[int(level)], file, line);
        buffer[len] = 0;
        m_fout << buffer;
        delete[] buffer;
        m_length += len;
    }

    va_list args;
    va_start(args, format);
    len = vsnprintf(nullptr, 0, format, args);
    va_end(args);
    if (len > 0) {
        char *content = new char[len + 1];
        va_start(args, format);
        vsnprintf(content, len + 1, format, args);
        va_end(args);
        content[len] = 0;
        m_fout << content;
        delete[] content;
        m_length += len;
    }
    m_fout << "\n";
    m_fout.flush();
    if (m_max_bytes > 0 && m_length > m_max_bytes)
        rotate();
}

void Logger::rotate() {
    close();
    time_t ticks = time(nullptr);
    struct tm *ptm = localtime(&ticks);
    char timestamp[32];
    memset(timestamp, 0, sizeof timestamp);
    strftime(timestamp, sizeof timestamp, "%Y-%m-%d_%H-%M-%S", ptm);
    std::string filename = m_filename + "_" + timestamp;
    if (rename(m_filename.c_str(), filename.c_str()) != 0)
        throw std::runtime_error("Could not rename log file:" + filename);
    open(filename);
}
