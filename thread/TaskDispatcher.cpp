//
// Created by cepher on 5/8/23.
//

#include <csignal>
#include "TaskDispatcher.h"
#include "../utility/Singleton.h"
#include "ThreadPool.h"
#include "../utility/logger/Logger.h"

using namespace crab;
using namespace crab::thread;
using namespace crab::logger;

TaskDispatcher::TaskDispatcher() = default;

TaskDispatcher::~TaskDispatcher() = default;

void TaskDispatcher::init(size_t threads) {
    Singleton<ThreadPool>::instance()->create(threads);
    start();
}

void TaskDispatcher::assign(Task *task) {
    debug("task dispatcher assign task!");
    m_mutex.lock();
    m_task.push_back(task);
    m_mutex.unlock();
    m_cond.signal();
}

void TaskDispatcher::handle(Task *task) {
    debug("task dispatcher handle task");
    auto tp = Singleton<ThreadPool>::instance();
    if (tp->get_idle_thread_num() > 0)
        tp->assign(task);
    else {
        m_mutex.lock();
        m_task.push_front(task);
        m_mutex.unlock();
        debug("all threads are busy!");
    }
}

void TaskDispatcher::run() {
    sigset_t mask;
    if (sigfillset(&mask) != 0) {
        error("thread manager sigfillset failed!");
        return;
    }
    if (pthread_sigmask(SIG_SETMASK, &mask, nullptr) != 0) {
        error("thread manager pthread_sigmask failed!");
        return;
    }
    while (true) {
        m_mutex.lock();
        while (m_task.empty())
            m_cond.wait(&m_mutex);
        auto task = m_task.front();
        m_task.pop_front();
        m_mutex.unlock();
        handle(task);
    }
}
