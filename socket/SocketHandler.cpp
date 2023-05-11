//
// Created by cepher on 5/10/23.
//

#include <iostream>
#include "SocketHandler.h"
#include "../utility/logger/Logger.h"
#include "../utility/Singleton.h"
#include "../task/TaskFactory.h"
#include "../thread/TaskDispatcher.h"
#include "ServerSocket.h"

using namespace crab::socket;
using namespace crab::logger;
using namespace crab::task;

SocketHandler::SocketHandler() = default;

SocketHandler::~SocketHandler() {
    if (m_epoll != nullptr) {
        delete m_epoll;
        m_epoll = nullptr;
    }
    if (m_server != nullptr) {
        delete m_server;
        m_server = nullptr;
    }
}

void SocketHandler::listen(const std::string &ip, int port) {
    m_server = new ServerSocket(ip, port);
    std::cout << "listen at http://" << ip << ":" << port << std::endl;
}

void SocketHandler::attach(Socket *socket) {
    AutoLock lock(&m_mutex);
    m_epoll->add(socket->m_sock_fd, (void *) socket, EPOLLONESHOT | EPOLLIN | EPOLLHUP | EPOLLERR);
}

void SocketHandler::detach(Socket *socket) {
    AutoLock lock(&m_mutex);
    m_epoll->del(socket->m_sock_fd, (void *) socket, EPOLLONESHOT | EPOLLIN | EPOLLHUP | EPOLLERR);
}

void SocketHandler::remove(Socket *socket) {
    socket->close();
    m_socket_pool.release(socket);
}

void SocketHandler::handle(int max_connections, int wait_time) {
    m_epoll = new EventPoller(false);
    m_epoll->create(max_connections);
    m_epoll->add(m_server->m_sock_fd, m_server, (EPOLLIN | EPOLLHUP | EPOLLERR));
    m_socket_pool.init(max_connections);

    debug("epoll wait time: %dms", wait_time);
    while (true) {
        int num = m_epoll->wait(wait_time);
        if (num == 0) {
            // debug("no events");
            continue;
        }
        for (int i = 0; i < num; i++) {
            if (m_server == static_cast<Socket *>(m_epoll->m_events[i].data.ptr)) {
                debug("socket accept event");
                int soctfd = m_server->accept();
                Socket *socket = m_socket_pool.allocate();
                if (socket == nullptr) {
                    error("socket pool is empty");
                    break;
                }
                socket->m_sock_fd = soctfd;
                socket->set_non_blocking();
                attach(socket);
            } else {
                auto socket = static_cast<Socket *>(m_epoll->m_events[i].data.ptr);
                if (m_epoll->m_events[i].events & EPOLLHUP) {
                    error("socket %d closed by peer.", socket->m_sock_fd);
                    detach(socket);
                    remove(socket);
                } else if (m_epoll->m_events[i].events & EPOLLERR) {
                    error("socket %d error.", socket->m_sock_fd);
                    detach(socket);
                    remove(socket);
                } else if (m_epoll->m_events[i].events & EPOLLIN) {
                    debug("socket read event");
                    detach(socket);
                    Task *task = TaskFactory::create(socket);
                    Singleton<TaskDispatcher>::instance()->assign(task);
                }
            }
        }
    }
}
