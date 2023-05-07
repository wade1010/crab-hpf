cmake_minimum_required(VERSION 3.25)
project(crab_hpf)

set(CMAKE_CXX_STANDARD 14)

add_executable(crab_hpf
        main.cpp utility/xml/Parser.cpp utility/xml/Parser.h utility/xml/Element.cpp utility/xml/Element.h)
