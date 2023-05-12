//
// Created by cepher on 5/12/23.
//

#ifndef CRAB_HPF_WORKTASK_H
#define CRAB_HPF_WORKTASK_H

#include <cstdint>
#include "../thread/Task.h"
#include "../socket/Socket.h"
using namespace crab::thread;
using namespace crab::socket;

namespace crab {
    namespace task {
        struct MsgHead {
            char flag[8];
            uint32_t cmd;
            uint32_t len;
        };

        const uint32_t  recv_buffer_size = 1024;

        class WorkTask :public Task{
        public:
            WorkTask(Socket *socket);

            ~WorkTask() override;

            void run() override;

            void destroy() override;
        };

    } // task
}

#endif //CRAB_HPF_WORKTASK_H
