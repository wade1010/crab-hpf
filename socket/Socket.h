//
// Created by cepher on 5/8/23.
//

#include <string>

#ifndef CRAB_HPF_SOCKET_H
#define CRAB_HPF_SOCKET_H

namespace crab {
    namespace socket {


        class Socket {
            std::string m_ip;
            int m_port;
            int m_sock_fd;
        public:
            Socket();

            Socket(const std::string &ip, int port);

            virtual ~Socket();

            bool bind(const std::string &ip, int port) const;

            bool listen(int backlog) const;

            bool connect(const std::string &ip, int port);

            bool close();

            int accept() const;

            int recv(char *buf, int len) const;

            int send(const char *buf, int len) const;

            bool set_non_blocking() const;

            bool set_send_buffer(size_t size) const;

            bool set_recv_buffer(size_t size) const;

            bool set_linger(bool active, int seconds) const;

            bool set_keepalive() const;

            bool set_reuse_addr() const;

            bool set_reuse_port() const;
        };


#endif //CRAB_HPF_SOCKET_H
    }
}