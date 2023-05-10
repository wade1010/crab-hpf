//
// Created by cepher on 5/10/23.
//

#ifndef CRAB_HPF_THREADPOOL_H
#define CRAB_HPF_THREADPOOL_H

#include <set>
#include "Thread.h"

namespace crab {
    namespace thread {

        class ThreadPool {
        public:
            ThreadPool();

            virtual ~ThreadPool();

            void create(int threads);

            Thread *get_idle_thread();

            void move_to_idle_list(Thread *thread);

            void move_to_busy_list(Thread *thread);

            size_t get_idle_thread_num();

            size_t get_busy_thread_num();

            void assign(Task *task);

        private:
            int m_threads;
            std::set<Thread *> m_list_idle;
            std::set<Thread *> m_list_busy;

            Mutex m_mutex_idle;
            Mutex m_mutex_busy;

            Condition m_cond_idle;
            Condition m_cond_busy;
        };
    }
}

#endif //CRAB_HPF_THREADPOOL_H
