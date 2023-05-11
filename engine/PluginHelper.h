//
// Created by cepher on 5/11/23.
//

#ifndef CRAB_HPF_PLUGINHELPER_H
#define CRAB_HPF_PLUGINHELPER_H

#include <map>
#include "Plugin.h"

namespace crab {
    namespace engine {

        typedef Plugin *(*create_func)();

        typedef void(*destroy_func)(Plugin *plugin);

        class PluginHelper {
        public:
            PluginHelper();

            ~PluginHelper();

            void load(const std::string &plugin);

            void unload(const std::string &plugin);

            void *get(const std::string &plugin, const std::string &symbol);

            void show();

        private:
            std::map<string, void *> m_plugins;
        };

    } // engine
}

#endif //CRAB_HPF_PLUGINHELPER_H
