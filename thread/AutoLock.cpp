//
// Created by cepher on 5/8/23.
//

#include "AutoLock.h"

crab::thread::AutoLock::AutoLock(Mutex *mutex) {
    m_mutex = mutex;
    m_mutex->lock();
}

crab::thread::AutoLock::~AutoLock() {
    m_mutex->unlock();
}
