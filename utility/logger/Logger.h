//
// Created by cepher on 5/7/23.
//



#ifndef CRAB_HPF_LOGGER_H
#define CRAB_HPF_LOGGER_H

#include <string>
#include <fstream>

#define debug(format, ...) crab::logger::Logger::instance()->log(crab::logger::Logger::Level::DEBUG,__FILE__,__LINE__,format,##__VA_ARGS__)
#define info(format, ...) crab::logger::Logger::instance()->log(crab::logger::Logger::Level::INFO,__FILE__,__LINE__,format,##__VA_ARGS__)
#define warn(format, ...) crab::logger::Logger::instance()->log(crab::logger::Logger::Level::WARN,__FILE__,__LINE__,format,##__VA_ARGS__)
#define error(format, ...) crab::logger::Logger::instance()->log(crab::logger::Logger::Level::ERROR,__FILE__,__LINE__,format,##__VA_ARGS__)
#define fatal(format, ...) crab::logger::Logger::instance()->log(crab::logger::Logger::Level::FATAL,__FILE__,__LINE__,format,##__VA_ARGS__)

namespace crab {
    namespace logger {
        class Logger {
        public:
            enum class Level {
                DEBUG = 0,
                INFO,
                WARN,
                ERROR,
                FATAL
            };

            static Logger *instance();

            void open(const std::string &filename);

            void close();

            void log(Level level, const char *file, int line, const char *format, ...);

        private:
            Logger();

            ~Logger();

            void rotate();

        private:
            std::string m_filename;
            std::ofstream m_fout;
            int m_max_bytes;
            Level m_level;
            long m_length;
            static const char *s_level[5];
            static Logger *m_instance;
        };


    }
}
#endif //CRAB_HPF_LOGGER_H
