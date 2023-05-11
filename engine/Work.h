//
// Created by cepher on 5/11/23.
//

#ifndef CRAB_HPF_WORK_H
#define CRAB_HPF_WORK_H

#include <string>
#include <vector>
#include "Plugin.h"
#include "Context.h"

namespace crab {
    namespace engine {

        class Work {
        public:
            Work();

            Work(std::string name, bool is_switch);

            ~Work();

            void append(Plugin *plugin);

            void set_name(const std::string &name);

            const std::string &get_name() const;

            void set_switch(bool switch_flag);

            bool get_switch() const;

            bool run(Context &ctx);

        protected:
            std::string m_name;
            bool m_switch;
            std::vector<Plugin *> m_plugins;

        };

    } // engine
}

#endif //CRAB_HPF_WORK_H
