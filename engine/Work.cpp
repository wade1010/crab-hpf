//
// Created by cepher on 5/11/23.
//

#include "Work.h"
#include "../utility/Singleton.h"
#include "PluginHelper.h"

#include <utility>

namespace crab {
    namespace engine {
        Work::Work() : m_switch(false) {

        }

        Work::Work(string name, bool is_switch) : m_name(std::move(name)), m_switch(false) {

        }

        Work::~Work() {
            for (auto p: m_plugins) {
                destroy_func func = (destroy_func) Singleton<PluginHelper>::instance()->get(p->get_name(), "destroy");
                func(p);
            }
        }

        void Work::append(Plugin *plugin) {
            m_plugins.push_back(plugin);
        }

        void Work::set_name(const std::string &name) {
            m_name = name;
        }

        const std::string &Work::get_name() const {
            return m_name;
        }

        void Work::set_switch(bool switch_flag) {
            m_switch = switch_flag;
        }

        bool Work::get_switch() const {
            return m_switch;
        }

        void Work::run(Context &ctx) {
            for (auto p: m_plugins) {
                if (p->get_switch())
                    if (!p->run(ctx))
                        break;
            }
        }
    } // engine
}