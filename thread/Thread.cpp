//
// Created by cepher on 5/8/23.
//

#include "Thread.h"
#include "AutoLock.h"

using namespace crab::thread;

Thread::Thread() : m_tid(0), m_task(nullptr) {

}

Thread::~Thread() = default;

void Thread::start() {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&m_tid,&attr,thread_func,(void *)this);
    pthread_attr_destroy(&attr);
}

void Thread::stop() {
    pthread_exit(PTHREAD_CANCELED);
}

void Thread::set_task(Task *task) {
    m_mutex.lock();
    m_task = task;
    m_cond.signal();
    m_mutex.unlock();
}

Task *Thread::get_task() {
    AutoLock lock(&m_mutex);
    return m_task;
}

void *Thread::thread_func(void *ptr) {
    auto *thread = (Thread *) ptr;
    thread->run();
    return ptr;
}
