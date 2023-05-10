//
// Created by cepher on 5/8/23.
//



#ifndef CRAB_HPF_TASKDISPATCHER_H
#define CRAB_HPF_TASKDISPATCHER_H

#include <list>
#include "Task.h"
#include "Thread.h"

namespace crab {
    namespace thread {

        class TaskDispatcher : public Thread {
        public:
            TaskDispatcher();

            ~TaskDispatcher();

            void init(size_t threads);

            void assign(Task *task);

            void handle(Task *task);

            virtual void run();

        protected:
            std::list<Task *> m_task;
        };
    }
}
#endif //CRAB_HPF_TASKDISPATCHER_H
