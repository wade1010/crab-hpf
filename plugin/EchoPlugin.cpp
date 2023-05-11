//
// Created by cepher on 5/11/23.
//

#include "EchoPlugin.h"
#include "../utility/Singleton.h"
#include "../utility/System.h"
#include "../utility/logger/Logger.h"

using namespace crab::logger;

namespace crab {
    namespace plugin {

        EchoPlugin::EchoPlugin() {
            auto sys = Singleton<System>::instance();
            Logger::instance()->open(sys->get_root_path() + "/log/echo.log");
        }

        EchoPlugin::~EchoPlugin() = default;

        bool EchoPlugin::run(Context &ctx) {
            auto &input = ctx.ref<std::string>("intput");
            info(input.c_str());
            ctx.ref<std::string>("output") = input + " echo plugin run!";
            return true;
        }
    }
}