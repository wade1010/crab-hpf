//
// Created by cepher on 5/10/23.
//

#ifndef CRAB_HPF_SOCKETHANDLER_H
#define CRAB_HPF_SOCKETHANDLER_H

#include <string>
#include "Socket.h"
#include "../utility/ObjectPool.h"
#include "EventPoller.h"

namespace crab {
    namespace socket {
        class SocketHandler {
        public:
            SocketHandler();

            ~SocketHandler();

            void listen(const std::string &ip, int port);

            void attach(Socket *socket);

            void detach(Socket *socket);

            void remove(Socket *socket1);

            void handle(int max_connections, int wait_time);

        private:
            EventPoller *m_epoll;
            Socket *m_server;
            ObjectPool<Socket> m_socket_pool;
            Mutex m_mutex;
        };

    }
}
#endif //CRAB_HPF_SOCKETHANDLER_H
