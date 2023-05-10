//
// Created by cepher on 5/10/23.
//
#include <cstring>
#include "ClientSocket.h"
#include "../utility/logger/Logger.h"

using namespace crab::socket;
using namespace crab::logger;

ClientSocket::ClientSocket() = default;

ClientSocket::ClientSocket(const std::string &ip, int port) : Socket(ip, port) {
    m_sock_fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sock_fd < 0) {
        error("create client socket error: errno=%d errstr=%s", errno, strerror(errno));
    }
    Socket::connect(ip, port);
}

ClientSocket::~ClientSocket() {
    close();
}
