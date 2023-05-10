//
// Created by cepher on 5/8/23.
//

#ifndef CRAB_HPF_SERVER_H
#define CRAB_HPF_SERVER_H

#include <string>

namespace crab {
    namespace server {


        class Server {
        public:
            Server();

            virtual ~Server();

            void listen(const std::string &ip, int port);

            void start();

            void set_threads(size_t num);

            void set_connects(size_t num);

            void set_wait_time(size_t wait_time);

        private:
            std::string m_ip;
            int m_port;
            size_t m_threads_num;
            size_t m_connection_num;
            size_t m_wait_time;
        };
    }
}
#endif //CRAB_HPF_SERVER_H
