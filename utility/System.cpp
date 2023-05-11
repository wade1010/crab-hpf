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
#include "../engine/Workflow.h"

using namespace crab::engine;

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

        logger::Logger::instance()->open(log_dir + "/server.log");

        auto ini = Singleton<ini::IniFile>::instance();
        ini->load_file(get_root_path() + "/config/dev.ini");

        Singleton<Workflow>::instance()->load(get_root_path() + "/config/workflow.xml");
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
        std::string first_program_path;
        std::string program_path = buf;
        std::string::size_type pos = program_path.find_last_of('/');
        while (pos != std::string::npos) {
            program_path = program_path.substr(0, pos);
            if (program_path.empty())
                break;
            std::ifstream ifs(program_path + "/CMakeLists.txt");
            if (ifs.good()) {
                // 找到了项目根目录
                ifs.close();
                break;
            } else if (first_program_path.empty()) {
                first_program_path = program_path;
            }
            ifs.close();
            pos = program_path.find_last_of('/');
        }

        if (program_path.empty() && first_program_path.empty())
            throw std::runtime_error("can not find root path!");
        else if (!program_path.empty())
            m_root_path = program_path;
        else
            m_root_path = first_program_path;
        return m_root_path;
    }

    void System::core_dump() {
        struct rlimit x{};
        int ret = getrlimit(RLIMIT_CORE, &x);
        x.rlim_cur = x.rlim_max;
        ret = setrlimit(RLIMIT_CORE, &x);

        ret = getrlimit(RLIMIT_DATA, &x);
        //这个值决定了config/dev.ini里面的threads数量，我设置500000000发现创建64个线程会有失败
        //怎么看失败呢？
        //调用pthread_create函数时，如果返回值为11，表示创建线程失败，错误代码为EAGAIN。
        // EAGAIN错误通常表示系统已经达到了允许创建的线程数目的上限，无法再创建新的线程。
        x.rlim_cur = 768000000;
        ret = setrlimit(RLIMIT_DATA, &x);
    }
} // crab