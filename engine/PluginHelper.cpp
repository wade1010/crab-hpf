//
// Created by cepher on 5/11/23.
//

#include <dlfcn.h>
#include "PluginHelper.h"
#include "../utility/Singleton.h"
#include "../utility/System.h"
#include "../utility/logger/Logger.h"

namespace crab {
    namespace engine {
        PluginHelper::PluginHelper() = default;

        PluginHelper::~PluginHelper() = default;

        void PluginHelper::load(const string &plugin) {
            if (plugin.empty()) {
                error("load plugin failure: plugin is empty.");
                return;
            }
            if (m_plugins.find(plugin) != m_plugins.end()) {
                debug("plugin is already exist.");
                return;
            }
            const string &filename = Singleton<System>::instance()->get_root_path() + "/plugin/" + plugin;
            void *handler = dlopen(filename.c_str(), RTLD_GLOBAL | RTLD_LAZY);
            if (handler == nullptr) {
                error("load plugin failure: %s", dlerror());
                return;
            }
            m_plugins[plugin] = handler;
        }

        void PluginHelper::unload(const string &plugin) {
            if (plugin.empty()) {
                error("unload plugin failure: plugin is empty.");
                return;
            }
            auto it = m_plugins.find(plugin);
            if (it == m_plugins.end()) {
                error("unload plugin failure: plugin is not exist.");
                return;
            }
            dlclose(it->second);
            m_plugins.erase(it);
        }

        void *PluginHelper::get(const string &plugin, const string &symbol) {
            auto it = m_plugins.find(plugin);
            if (it == m_plugins.end()) {
                load(plugin);
                it = m_plugins.find(plugin);
                if (it == m_plugins.end()) {
                    error("load plugin failed: %s", plugin.c_str());
                    return nullptr;
                }
            }
            void *func = dlsym(it->second, "create");
            if (func == nullptr)
                error("plugin: %s, undefined symbol: %s", plugin.c_str(), symbol.c_str());
            return func;
        }

        void PluginHelper::show() {
            for (auto p: m_plugins) {
                debug("plugin: name=%s handle=%x", p.first.c_str(), p.second);
            }
        }
    } // engine
}