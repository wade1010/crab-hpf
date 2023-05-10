//
// Created by cepher on 5/8/23.
//

#ifndef CRAB_HPF_TASK_H
#define CRAB_HPF_TASK_H

# include "Mutex.h"

namespace crab {
    namespace thread {
        class Task {
        public:
            Task();

            Task(void *data);

            virtual ~Task();

            void *get_data();

            void set_data(void *data);

            virtual void run() = 0;

            virtual void destroy() = 0;

        protected:
            void *m_data;
            Mutex m_mutex;
        };
    }
}
#endif //CRAB_HPF_TASK_H
