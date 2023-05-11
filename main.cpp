#include <iostream>
#include "utility/xml/Parser.h"
#include "utility/json/Parser.h"
#include "utility/ini/IniFile.h"
#include "utility/logger/Logger.h"
#include "utility/Singleton.h"
#include "server/Server.h"
#include "utility/System.h"

using namespace crab;

void test();

int main() {
//    test();
    auto sys = Singleton<System>::instance();
    sys->init();

    auto ini = Singleton<ini::IniFile>::instance();
    const std::string &ip = ini->get("server", "ip");
    int port = ini->get("server", "port");
    int threads = ini->get("server", "threads");
    int max_conn = ini->get("server", "max_conn");
    int wait_time = ini->get("server", "wait_time");

    if (max_conn <= threads) {
        max_conn = threads;
        warn("max_conn is smaller than the number of threads, so change it to the number of threads:%d", threads);
    }

    auto server = Singleton<server::Server>::instance();
    server->set_threads(threads);
    server->set_connects(max_conn);
    server->set_wait_time(wait_time);
    server->listen(ip, port);
    server->start();
    return 0;
}

void test() {
    std::cout << "===============test logger===============" << std::endl;
    crab::logger::Logger::instance()->open("../test_logger.log");
    debug("test logger");

    std::cout << "===============test server===============" << std::endl;
    auto serv = Singleton<server::Server>::instance();
    serv->set_threads(1000);
    serv->set_connects(10000);
    serv->set_wait_time(10);
    serv->listen("0.0.0.0", 8080);
    serv->start();
    //xml
    std::cout << "===============test xml===============" << std::endl;
    crab::xml::Parser xml_parser;
    xml_parser.load_file("../utility/xml/test.xml");
    xml_parser.parse();

    //json
    std::cout << "===============test json===============" << std::endl;

    crab::json::Parser json_parser;
    crab::json::Json j1;
    crab::json::Json j2 = crab::json::Json(true);
    crab::json::Json j3 = crab::json::Json(1111);
    crab::json::Json j4 = crab::json::Json(1.111);
    crab::json::Json j5 = crab::json::Json("c++");
    bool b = j2.asBool();
    int i = j3.asInt();
    double d = j4.asDouble();
    const std::string &s = j5.asString();
    std::cout << b << i << s << std::endl;

    //ini
    std::cout << "===============test init===============" << std::endl;
    crab::ini::IniFile ini_file;
    ini_file.load_file("../utility/ini/test.ini");
    ini_file.show();
}