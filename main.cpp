#include <iostream>
#include "utility/xml/Parser.h"
#include "utility/json/Parser.h"

using namespace crab;

int main() {
    crab::xml::Parser xml_parser;
    xml_parser.load_file("../utility/xml/test.xml");
    xml_parser.parse();
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
    return 0;
}