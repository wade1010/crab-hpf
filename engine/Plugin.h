//
// Created by cepher on 5/11/23.
//

#ifndef CRAB_HPF_PLUGIN_H
#define CRAB_HPF_PLUGIN_H

#include <string>
#include <utility>
#include "Context.h"

namespace crab {
    namespace engine {

        class Plugin {
        public:
            Plugin() : m_switch(false) {

            }

            Plugin(std::string name, bool switch_flag) : m_name(std::move(name)), m_switch(switch_flag) {

            }

            virtual ~Plugin() {}

            void set_name(const std::string &name) {
                m_name = name;
            }

            const std::string &get_name() const {
                return m_name;
            }

            void set_switch(bool switch_flag) {
                m_switch = switch_flag;
            }

            bool get_switch() const {
                return m_switch;
            }

            virtual bool run(Context &ctx) = 0;


        protected:
            std::string m_name;
            bool m_switch;
        };

//        宏定义的语法可以自由地使用反斜杠（\）在多行中换行，以便更好地阅读和组织代码
        #define DEFINE_PLUGIN(classType)                \
        extern "C" Plugin* create(){                    \
            return new (std::nothrow) classType();      \
        }                                               \
        extern "C" void destroy(Plugin * plugin){       \
            delete plugin;                               \
            plugin= nullptr;                             \
        }
    } // engine
}

#endif //CRAB_HPF_PLUGIN_H
