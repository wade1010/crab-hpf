//
// Created by cepher on 5/10/23.
//

#ifndef CRAB_HPF_SERVERSOCKET_H
#define CRAB_HPF_SERVERSOCKET_H

#include "Socket.h"

namespace crab {
    namespace socket {
        class ServerSocket : public Socket {
            ServerSocket();
            ServerSocket(const std::string &ip, int port);
            virtual ~ServerSocket();
        };

    }
}
#endif //CRAB_HPF_SERVERSOCKET_H
