//
// Created by cepher on 5/10/23.
//

#ifndef CRAB_HPF_EVENTPOLLER_H
#define CRAB_HPF_EVENTPOLLER_H

#include <sys/epoll.h>

namespace crab {
    namespace socket {

        class EventPoller {
        public:
            /**
             * 构造函数
             * @param et 默认是ET模式
             */
            EventPoller(bool et = true);

            ~EventPoller();

            /**
             * 生成epoll句柄
             * @param max epoll服务需要支持的最大连接数
             */
            void create(int max);

            /**
             * 添加监听句柄
             * @param fd 句柄
             * @param ptr 辅助的数据，可以后续在epoll_event中获取到
             * @param events 需要监听的事件EPOLLIN|EPOLLOUT
             */
            void add(int fd, void *ptr, __uint32_t events);

            /**
             * 修改句柄事件
             * @param fd 句柄
             * @param ptr 辅助的数据，可以后续在epoll_event中获取到
             * @param events 需要监听的事件EPOLLIN|EPOLLOUT
             */
            void mod(int fd, void *ptr, __uint32_t events);

            /**
             * 删除句柄事件
             * @param fd 句柄
             * @param ptr 辅助的数据，可以后续在epoll_event中获取到
             * @param events 需要监听的事件EPOLLIN|EPOLLOUT
             */
            void del(int fd, void *ptr, __uint32_t events);

            /**
             * 等待事件
             * @param millisecond 毫秒
             * @return int 有时间触发的句柄数
             */
            int wait(int millisecond);

        protected:
            /**
             * 控制 epoll，将EPOLL设为边缘触发EPOLLET模式
             * @param fd 句柄，在create函数时被赋值
             * @param ptr 辅助的数据, 可以后续在epoll_event中获取到
             * @param events 需要监听的事件
             *               EPOLLIN   表示对应的文件描述符可以读
             *               EPOLLOUT 表示对应的文件描述符可以写
             *               EPOLLPRI 表示对应的文件描述符有紧急的数据可读
             *               EPOLLERR 示对应的文件描述符发生错误
             *               EPOLLHUP 示对应的文件描述符被挂断
             *               EPOLLET 示对应的文件描述符有事件发生
             * @param op 控制epoll文件描述符上的事件：注册、修改、删除
             *           EPOLL_CTL_ADD:注册新的fd到epfd中
             *           EPOLL_CTL_MOD:修改已经注册的fd的监听事件
             *           EPOLL_CTL_DEL:从epfd中删除一个fd
             */
            void ctrl(int fd, void *ptr, __uint32_t events, int op) const;

        protected:
            /**
               * epoll
               */
            int m_epfd;

            /**
             * 最大连接数
             */
            int m_max_connections;

            /**
             * 事件集
             */
            struct epoll_event *m_events;

            /**
             * 是否是ET模式
             */
            bool m_et;
        };

    }
}

#endif //CRAB_HPF_EVENTPOLLER_H
