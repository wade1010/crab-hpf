//
// Created by cepher on 5/10/23.
//

#ifndef CRAB_HPF_CLIENTSOCKET_H
#define CRAB_HPF_CLIENTSOCKET_H

#include <string>
#include "Socket.h"

namespace crab {
    namespace socket {
        class ClientSocket: public Socket{
        public:
            ClientSocket();
            ClientSocket(const std::string &ip,int port);
            virtual ~ClientSocket();
        };

    }
}
#endif //CRAB_HPF_CLIENTSOCKET_H
