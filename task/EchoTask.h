//
// Created by cepher on 5/10/23.
//

#ifndef CRAB_HPF_ECHOTASK_H
#define CRAB_HPF_ECHOTASK_H

#include "../thread/Task.h"
#include "../socket/Socket.h"

using namespace crab::thread;
using namespace crab::socket;

namespace crab {
    namespace task {

        class EchoTask : public Task {
        public:
            EchoTask(Socket * socket);

            virtual ~EchoTask();

            virtual void run();

            virtual void destroy();
        };

    } // task
} // crab

#endif //CRAB_HPF_ECHOTASK_H
