//
// Created by cepher on 5/10/23.
//

#ifndef CRAB_HPF_TASKFACTORY_H
#define CRAB_HPF_TASKFACTORY_H

#include "../thread/Task.h"
#include "../socket/Socket.h"
#include "EchoTask.h"
#include "WorkTask.h"

using namespace crab::thread;
using namespace crab::socket;

namespace crab {
    namespace task {
        class TaskFactory {
        public:
            static Task *create(Socket *socket) {
                return new WorkTask(socket);
//                return new EchoTask(socket);
            }
        };
    }
}
#endif //CRAB_HPF_TASKFACTORY_H
