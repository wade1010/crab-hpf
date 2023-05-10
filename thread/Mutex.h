//
// Created by cepher on 5/8/23.
//

#ifndef CRAB_HPF_MUTEX_H
#define CRAB_HPF_MUTEX_H

#include <pthread.h>

namespace crab {
    namespace thread {
        class Mutex {
            friend class Condition;

        public:
            Mutex();

            ~Mutex();

            int lock();

            int try_lock();

            int unlock();

        private:
            pthread_mutex_t m_mutex;
        };
    }
}
#endif //CRAB_HPF_MUTEX_H
