//
// Created by cepher on 5/8/23.
//

#include "Condition.h"

using namespace crab::thread;

Condition::Condition(): m_cond() {
    pthread_cond_init(&m_cond, nullptr);
}

Condition::~Condition() {
    pthread_cond_destroy(&m_cond);
}

int Condition::wait(Mutex *mutex) {
    return pthread_cond_wait(&m_cond,&(mutex->m_mutex));
}

int Condition::signal() {
    return pthread_cond_signal(&m_cond);
}
