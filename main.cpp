#include <iostream>
#include "utility/xml/Parser.h"
#include "utility/json/Parser.h"
#include "utility/ini/IniFile.h"
#include "utility/logger/Logger.h"

using namespace crab;

int main() {
    //xml
    std::cout<<"===============test xml==============="<<std::endl;
    crab::xml::Parser xml_parser;
    xml_parser.load_file("../utility/xml/test.xml");
    xml_parser.parse();

    //json
    std::cout<<"===============test json==============="<<std::endl;

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
    std::cout<<"===============test init==============="<<std::endl;
    crab::ini::IniFile ini_file;
    ini_file.load_file("../utility/ini/test.ini");
    ini_file.show();

    std::cout<<"===============test logger==============="<<std::endl;
    crab::logger::Logger::instance()->open("../test_logger.log");
    debug("test logger");
    return 0;
}