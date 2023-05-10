//
// Created by cepher on 5/8/23.
//

#include "Server.h"
#include "../thread/TaskDispatcher.h"
#include "../socket/SocketHandler.h"
#include "../utility/Singleton.h"

using namespace crab::server;
using namespace crab::thread;
using namespace crab::socket;

Server::Server() : m_port(8080), m_connection_num(1024), m_threads_num(1024), m_wait_time(10) {
};

Server::~Server() = default;

void Server::listen(const std::string &ip, int port) {
    m_ip = ip;
    m_port = port;
}

void Server::start() {
    crab::Singleton<TaskDispatcher>::instance()->init(m_threads_num);
    auto socket_handler = Singleton<SocketHandler>::instance();
    socket_handler->listen(m_ip, m_port);
    socket_handler->handle(m_connection_num, m_wait_time);
}

void Server::set_threads(size_t num) {
    m_threads_num = num;
}

void Server::set_connects(size_t num) {
    m_connection_num = num;
}

void Server::set_wait_time(size_t wait_time) {
    m_wait_time = wait_time;
}
