//
// Created by cepher on 5/10/23.
//

#include "ThreadPool.h"
#include "AutoLock.h"
#include "../utility/logger/Logger.h"
#include "WorkerThread.h"

using namespace crab::thread;


ThreadPool::ThreadPool() = default;

ThreadPool::~ThreadPool() = default;

void ThreadPool::create(int threads) {
    AutoLock lock(&m_mutex_idle);
    m_threads = threads;
    while (threads-- > 0) {
        Thread *thread = new WorkerThread();
        debug("create thread %x", thread);
        m_list_idle.insert(thread);
        thread->start();
    }
}

Thread *ThreadPool::get_idle_thread() {
    AutoLock lock(&m_mutex_idle);
    while (m_list_idle.empty())
        m_cond_idle.wait(&m_mutex_idle);
    return *m_list_idle.begin();
}

void ThreadPool::move_to_idle_list(Thread *thread) {
    m_mutex_idle.lock();
    m_list_idle.insert(thread);
    m_cond_idle.signal();//唤醒 在idle list空的时候wait
    m_mutex_idle.unlock();

    m_mutex_busy.lock();
    auto it = m_list_busy.find(thread);
    if (it != m_list_busy.end())
        m_list_busy.erase(it);
    m_cond_busy.signal();//唤醒 busy list满的时候的wait
    m_mutex_busy.unlock();
}

void ThreadPool::move_to_busy_list(Thread *thread) {
    m_mutex_busy.lock();
    while (m_list_busy.size() == m_threads)
        m_cond_busy.wait(&m_mutex_busy);
    m_list_busy.insert(thread);
    m_cond_busy.signal();
    m_mutex_busy.unlock();

    m_mutex_idle.lock();
    auto it = m_list_idle.find(thread);
    if (it != m_list_idle.end())
        m_list_idle.erase(it);
    m_mutex_idle.unlock();
}

size_t ThreadPool::get_idle_thread_num() {
    AutoLock lock(&m_mutex_idle);
    return m_list_idle.size();
}

size_t ThreadPool::get_busy_thread_num() {
    AutoLock lock(&m_mutex_busy);
    return m_list_busy.size();
}

void ThreadPool::assign(Task *task) {
    if (task == nullptr) {
        error("assign a null task!");
        return;
    }
    debug("assign a new task %x to thread pool", task);

    auto thread = get_idle_thread();
    if (thread == nullptr)
        error("thread pool is null,assign task failed!");
    move_to_busy_list(thread);
    thread->set_task(task);
}
