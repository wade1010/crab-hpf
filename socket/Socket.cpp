//
// Created by cepher on 5/8/23.
//

#include <cstring>
#include "Socket.h"
#include "../utility/logger/Logger.h"

using namespace crab::socket;
using namespace crab::logger;

Socket::Socket() : m_port(0), m_sock_fd(0) {

}

Socket::Socket(const std::string &ip, int port) : m_ip(ip), m_port(port), m_sock_fd(0) {

}

Socket::~Socket() {
    close();
}

bool Socket::bind(const std::string &ip, int port) const {
    struct sockaddr_in sockaddr{};
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    if (!ip.empty())
        sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    else
        sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockaddr.sin_port = htons(port);
    if (::bind(m_sock_fd, (struct sockaddr *) &sockaddr, sizeof sockaddr) < 0) {
        error("socket bind error:errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::listen(int backlog) const {
    if (::listen(m_sock_fd, backlog) < 0) {
        error("socket listen error:errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::connect(const std::string &ip, int port) {
    struct sockaddr_in sockaddr{};
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_port = htons(port);
    if (::connect(m_sock_fd, (struct sockaddr *) &sockaddr, sizeof(sockaddr)) < 0) {
        error("socket connect error: errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::close() {
    if (m_sock_fd > 0) {
        ::close(m_sock_fd);
        m_sock_fd = 0;
    }
    return true;
}

int Socket::accept() const {
    return m_sock_fd;
}

int Socket::recv(char *buf, int len) const {
    return ::recv(m_sock_fd, buf, len, 0);
}

int Socket::send(const char *buf, int len) const {
    return ::send(m_sock_fd, buf, len, 0);
}

bool Socket::set_non_blocking() const {
    int flags = fcntl(m_sock_fd, F_GETFL, 0);
    if (flags < 0) {
        error("Socket::set_non_blocking:1:errno=%d,errstr=%s", errno, strerror(errno));
        return false;
    }
    flags |= O_NONBLOCK;
    if (fcntl(m_sock_fd, F_SETFL, flags) < 0) {
        error("Socket::set_non_blocking:2:errno=%d,errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_send_buffer(size_t size) const {
    if (setsockopt(m_sock_fd, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size)) < 0) {
        error("socket set recv buffer error: errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_recv_buffer(size_t size) const {
    if (setsockopt(m_sock_fd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size)) < 0) {
        error("socket set recv buffer error: errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_linger(bool active, int seconds) const {
    struct linger l{};
    memset(&l, 0, sizeof(l));
    l.l_onoff = active ? 1 : 0;
    l.l_linger = seconds;
    if (setsockopt(m_sock_fd, SOL_SOCKET, SO_LINGER, &l, sizeof(l)) < 0) {
        error("socket set sock linger error: errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_keepalive() const {
    int flags = 1;
    if (setsockopt(m_sock_fd, SOL_SOCKET, SO_KEEPALIVE, &flags, sizeof(flags)) < 0) {
        error("socket set sock keep alive error: errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_reuse_addr() const {
    int flags = 1;
    if (setsockopt(m_sock_fd, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags)) < 0) {
        error("socket set sock reuser addr error: errno=%s errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_reuse_port() const {
    int flags = 1;
    if (setsockopt(m_sock_fd, SOL_SOCKET, SO_REUSEPORT, &flags, sizeof(flags)) < 0) {
        error("socket set sock reuser port error: errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}
