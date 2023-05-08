//
// Created by cepher on 5/8/23.
//

#ifndef CRAB_HPF_AUTOLOCK_H
#define CRAB_HPF_AUTOLOCK_H

#include "Mutex.h"

namespace crab {
    namespace thread {

        class AutoLock {
            Mutex *m_mutex;
        public:
            explicit AutoLock(Mutex *mutex);

            ~AutoLock();
        };

    }
}
#endif //CRAB_HPF_AUTOLOCK_H
