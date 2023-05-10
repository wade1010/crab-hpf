//
// Created by cepher on 5/10/23.
//
#include <sys/resource.h>
#include <unistd.h>
#include <stdexcept>
#include <dirent.h>
#include <sys/stat.h>
#include "System.h"
#include "./logger/Logger.h"
#include "./ini/IniFile.h"
#include "Singleton.h"


namespace crab {

    System::System() = default;

    System::~System() = default;

    void System::init() {
        core_dump();

        const std::string &log_dir = get_root_path() + "/log";
        auto *dir = opendir(log_dir.c_str());
        if (dir == nullptr)
            mkdir(log_dir.c_str(), 0755);
        else
            closedir(dir);

        logger::Logger::instance()->open(log_dir + "/main.log");

        auto ini = Singleton<ini::IniFile>::instance();
        ini->load_file(get_root_path() + "/config/dev.ini");



    }

    std::string System::get_root_path() {
        if (!m_root_path.empty())
            return m_root_path;

        // 获取程序所在的绝对路径
        char buf[1024];
        ssize_t len = ::readlink("/proc/self/exe", buf, sizeof(buf) - 1);
        if (len == -1) {
            return "";
        }
        buf[len] = '\0';
        std::string program_path = buf;
        std::string::size_type pos = program_path.find_last_of('/');
        if (pos == std::string::npos)
            throw std::logic_error("get root path error");
        m_root_path = program_path.substr(0, pos);
        return m_root_path;
    }

    void System::core_dump() {
        struct rlimit x;
        int ret = getrlimit(RLIMIT_CORE, &x);
        x.rlim_cur = x.rlim_max;
        ret = setrlimit(RLIMIT_CORE, &x);

        ret = getrlimit(RLIMIT_DATA, &x);
        x.rlim_cur = 500000000;//500MB
        ret = setrlimit(RLIMIT_DATA, &x);
    }
} // crab