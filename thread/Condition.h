//
// Created by cepher on 5/8/23.
//
#include "Mutex.h"

namespace crab {
    namespace thread {
#ifndef CRAB_HPF_CONDITION_H
#define CRAB_HPF_CONDITION_H


        class Condition {
        public:
            Condition();
            ~Condition();

            int wait(Mutex *mutex);
            int signal();
        protected:
            pthread_cond_t  m_cond;
        };


#endif //CRAB_HPF_CONDITION_H
    }
}