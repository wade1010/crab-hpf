cmake_minimum_required(VERSION 3.15)
project(crab_hpf)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)

add_executable(crab_hpf
        main.cpp utility/xml/Parser.cpp utility/xml/Parser.h utility/xml/Element.cpp utility/xml/Element.h
        utility/json/Parser.cpp utility/json/Parser.h utility/json/Json.cpp utility/json/Json.h
        utility/ini/IniFile.cpp utility/ini/IniFile.h utility/logger/Logger.cpp utility/logger/Logger.h
        server/Server.cpp server/Server.h socket/Socket.cpp socket/Socket.h utility/Singleton.h
        thread/TaskDispatcher.cpp thread/TaskDispatcher.h thread/Thread.cpp thread/Thread.h thread/Task.cpp
        thread/Task.h thread/Mutex.cpp thread/Mutex.h thread/Condition.cpp thread/Condition.h thread/AutoLock.cpp
        thread/AutoLock.h thread/ThreadPool.cpp thread/ThreadPool.h thread/WorkerThread.cpp thread/WorkerThread.h
        socket/ServerSocket.cpp socket/ServerSocket.h socket/SocketHandler.cpp socket/SocketHandler.h
        utility/ObjectPool.h socket/EventPoller.cpp socket/EventPoller.h socket/ClientSocket.cpp
        socket/ClientSocket.h utility/System.cpp utility/System.h)

target_link_libraries(crab_hpf ${CMAKE_THREAD_LIBS_INIT})