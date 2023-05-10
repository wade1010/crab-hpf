//
// Created by cepher on 5/10/23.
//
#include <cstring>
#include "ServerSocket.h"
#include "../utility/logger/Logger.h"
using namespace crab::socket;
using namespace crab::logger;
ServerSocket::ServerSocket() = default;

ServerSocket::ServerSocket(const std::string &ip, int port) : Socket(ip, port) {
    m_sock_fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sock_fd<0){
        error("create server socket error: errno=%d,errstr=%s", errno, strerror(errno));
        return;
    }
    set_non_blocking();
    set_recv_buffer(10240);
    set_send_buffer(10240);
    set_linger(true, 0);
    set_keepalive();
    set_reuse_addr();
    bind(ip, port);
    listen(1024);
}

ServerSocket::~ServerSocket() {
    close();
}
