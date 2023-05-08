cmake_minimum_required(VERSION 3.15)
project(crab_hpf)

set(CMAKE_CXX_STANDARD 14)

add_executable(crab_hpf
        main.cpp utility/xml/Parser.cpp utility/xml/Parser.h utility/xml/Element.cpp utility/xml/Element.h
        utility/json/Parser.cpp utility/json/Parser.h utility/json/Json.cpp utility/json/Json.h utility/ini/IniFile.cpp utility/ini/IniFile.h utility/logger/Logger.cpp utility/logger/Logger.h server/Server.cpp server/Server.h socket/Socket.cpp socket/Socket.h)
