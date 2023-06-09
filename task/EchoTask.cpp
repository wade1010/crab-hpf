//
// Created by cepher on 5/10/23.
//

#include <cstring>
#include "EchoTask.h"
#include "../utility/logger/Logger.h"
#include "../utility/Singleton.h"
#include "../socket/SocketHandler.h"

using namespace crab::logger;

namespace crab {
    namespace task {

        EchoTask::EchoTask(Socket *socket) : Task(socket) {

        }

        EchoTask::~EchoTask() = default;

        void EchoTask::run() {
            debug("echo task run");
            SocketHandler *handler = Singleton<SocketHandler>::instance();

            auto socket = static_cast<Socket *>(m_data);
            char buf[1024];
            memset(buf, 0, 1024);
            int len = socket->recv(buf, 1024);
            if (len > 0) {
                debug("recv msg len: %d msg data: %s", len, buf);
                socket->send(buf, len);
                handler->attach(socket);
            } else {
                debug("echo task socket closed by peer");
                handler->remove(socket);
            }
        }

        void EchoTask::destroy() {
            debug("echo task destroy");
            delete this;
        }
    } // task
} // crab