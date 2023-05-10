//
// Created by cepher on 5/8/23.
//
#ifndef CRAB_HPF_THREAD_H
#define CRAB_HPF_THREAD_H

#include "Task.h"
#include "Condition.h"

namespace crab {
    namespace thread {

        class Thread {
        public:
            Thread();

            virtual ~Thread();

            virtual void run() = 0;

            void start();

            static void stop();

            void set_task(Task *task);

            Task *get_task();

        protected:
            static void *thread_func(void *ptr);

        protected:
            pthread_t m_tid;
            Task *m_task;
            Mutex m_mutex;
            Condition m_cond;
        };

    }
}
#endif //CRAB_HPF_THREAD_H
