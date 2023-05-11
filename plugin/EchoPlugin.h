//
// Created by cepher on 5/11/23.
//

#ifndef CRAB_HPF_ECHOPLUGIN_H
#define CRAB_HPF_ECHOPLUGIN_H

#include "../engine/Plugin.h"

using namespace crab::engine;

namespace crab {
    namespace plugin {


        class EchoPlugin : public Plugin {
        public:
            EchoPlugin();

            virtual ~EchoPlugin();

            virtual bool run(Context &ctx);
        };
        DEFINE_PLUGIN(EchoPlugin)
    }
}
#endif //CRAB_HPF_ECHOPLUGIN_H
