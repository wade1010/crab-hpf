//
// Created by cepher on 5/11/23.
//

#include "Workflow.h"
#include "../utility/xml/Parser.h"
#include "../utility/logger/Logger.h"
#include "../utility/Singleton.h"
#include "../engine/PluginHelper.h"

namespace crab {
    namespace engine {
        Workflow::Workflow() = default;

        Workflow::~Workflow() {
            for (auto p: m_works) {
                delete p.second;
                p.second = nullptr;
            }
            m_works.clear();
        }

        bool Workflow::load(const string &file) {
            Parser xml_parser;
            xml_parser.load_file(file);
            Element root = xml_parser.parse();
            info("load workflow success: %s", file.c_str());
            for (auto it = root.begin(); it != root.end(); it++) {
                auto switch_flag = it->attr("switch") == "on";
                if (!switch_flag)
                    continue;
                auto name = it->attr("name");
                Work *work = new Work();
                work->set_name(name);
                work->set_switch(switch_flag);
                if (!load_plugin(work, *it))
                    return false;
                m_works[name] = work;
            }
            return true;
        }

        bool Workflow::run(const string &work, const string &input, const string &output) {
            return false;
        }

        bool Workflow::load_plugin(Work *work, Element &element) {
            for (auto it = element.begin(); it != element.end(); it++) {
                const string &name = it->attr("name");
                if (it->name() != "plugin") {
                    error("plugin %s element: %s is not supported", name.c_str(), it->name().c_str());
                    return false;
                }
                create_func func = (create_func) Singleton<PluginHelper>::instance()->get(name, "create");
                if (func == nullptr)
                    continue;
                Plugin *plugin = func();
                plugin->set_name(name);
                auto switch_flag = it->attr("switch");
                plugin->set_switch(switch_flag == "on");
                work->append(plugin);
            }
            return true;
        }
    }
}