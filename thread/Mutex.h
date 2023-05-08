//
// Created by cepher on 5/8/23.
//
#include <pthread.h>
namespace crab {
    namespace thread {
#ifndef CRAB_HPF_MUTEX_H
#define CRAB_HPF_MUTEX_H

class Mutex {
friend class Condition;
public:
    Mutex();
    ~Mutex();
    int lock();

    int try_lock();

    int unlock();
private:
    pthread_mutex_t  m_mutex;
};


#endif //CRAB_HPF_MUTEX_H
    }
}