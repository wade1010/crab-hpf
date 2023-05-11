//
// Created by cepher on 5/10/23.
//

#ifndef CRAB_HPF_WORKERTHREAD_H
#define CRAB_HPF_WORKERTHREAD_H

#include "Thread.h"

namespace crab {
    namespace thread {
        class WorkerThread : public Thread {
        public:
            WorkerThread();

            virtual ~WorkerThread();

            virtual void run();

            static void cleanup(void *ptr);
        };
    }
}
#endif //CRAB_HPF_WORKERTHREAD_H
