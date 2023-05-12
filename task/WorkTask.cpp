//
// Created by cepher on 5/12/23.
//

#include "WorkTask.h"
#include "../utility/logger/Logger.h"
#include "../utility/Singleton.h"
#include "../socket/SocketHandler.h"

namespace crab {
    namespace task {
        WorkTask::WorkTask(Socket *socket) : Task(socket) {

        }

        WorkTask::~WorkTask() = default;

        void WorkTask::run() {
            debug("work task running");
            auto handler = Singleton<SocketHandler>::instance();
            auto socket = static_cast<Socket *>(m_data);

            MsgHead msg_head{};
            //todo
        }

        void WorkTask::destroy() {
            debug("work job destroy");
            delete this;
        }
    } // task
}