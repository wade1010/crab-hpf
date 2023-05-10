//
// Created by cepher on 5/10/23.
//

#include <csignal>
#include "WorkerThread.h"
#include "../utility/logger/Logger.h"
#include "../utility/Singleton.h"
#include "ThreadPool.h"

using namespace crab::thread;

WorkerThread::WorkerThread() = default;

WorkerThread::~WorkerThread() = default;

[[noreturn]] void WorkerThread::run() {
//    使用sigfillset函数将所有的信号添加到信号集中，
//    并使用pthread_sigmask函数将信号集添加到线程的信号屏蔽字中，
//    以防止在执行任务时被信号中断，确保了任务的可靠性。
    sigset_t mask;
    if (sigfillset(&mask) != 0)
        error("sigfillset failed!");
    if (pthread_sigmask(SIG_SETMASK, &mask, nullptr) != 0)
        error("pthread_sigmask faield!");
    pthread_cleanup_push(cleanup, this);
        while (true) {
            //开始等任务
            m_mutex.lock();
            while (m_task== nullptr)
                m_cond.wait(&m_mutex);
            m_mutex.unlock();
            //结束等任务
            //使用pthread_setcancelstate函数来控制线程的取消状态，
            // 确保任务能够安全地执行完毕
            int old_state = 0;
            int rc = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_state);
            m_task->run();
            m_task->destroy();
            m_task= nullptr;

            Singleton<ThreadPool>::instance()->move_to_idle_list(this);

            rc = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &old_state);
            //线程取消点函数，用于检测当前线程是否有取消请求。如果有，当前线程将被取消。
            pthread_testcancel();
        }
    pthread_cleanup_pop(1);

//    使用pthread_cleanup_push宏将cleanup函数和this指针推入线程栈中，
//    以保证在线程退出时可以执行cleanup函数，释放线程占用的资源。
}

void WorkerThread::cleanup(void *ptr) {
    info("worker thread cleanup handler %x", ptr);
}
