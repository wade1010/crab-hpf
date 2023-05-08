//
// Created by cepher on 5/8/23.
//

#include "Server.h"

using namespace crab::server;

Server::Server() : m_port(8080), m_connects_num(1024), m_threads_num(1024), m_wait_time(10) {
};

Server::~Server() = default;

void Server::listen(const std::string &ip, int port) {
    m_ip = ip;
    m_port = port;
}

void Server::start() {
//todo
}

void Server::set_threads(size_t num) {
    m_threads_num = num;
}

void Server::set_connects(size_t num) {
    m_connects_num = num;
}

void Server::set_wait_time(size_t wait_time) {
    m_wait_time = wait_time;
}
