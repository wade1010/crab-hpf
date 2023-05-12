//
// Created by cepher on 5/12/23.
//

#include <cstring>
#include <sstream>
#include "WorkTask.h"
#include "../utility/logger/Logger.h"
#include "../utility/Singleton.h"
#include "../socket/SocketHandler.h"
#include "../engine/Workflow.h"

using crab::engine::Workflow;
namespace crab {
    namespace task {
        WorkTask::WorkTask(Socket *socket) : Task(socket) {

        }

        WorkTask::~WorkTask() = default;

        void WorkTask::run() {
            debug("work task running");
            auto handler = Singleton<SocketHandler>::instance();
            auto socket = static_cast<Socket *>(m_data);

            MsgHead msg_head{};
            //先接收消息头
            int len = socket->recv(reinterpret_cast<char *>(&msg_head), sizeof(msg_head));
            if (len == 0) {
                error("socket closed by peer");
                handler->remove(socket);
                return;
            }
            if (len == -1) {
                error("socket recv,errno=%d errstr=%s", errno, strerror(errno));
                handler->attach(socket);
                return;
            }

            if (len != sizeof(msg_head)) {
                error("recv msg head error length: %d, errno: %d", len, errno);
                handler->remove(socket);
                return;
            }
            info("recv msg head len: %d, flag: %s, cmd: %d, body len: %d", len, msg_head.flag, msg_head.cmd,
                 msg_head.len);
            if (strncmp(msg_head.flag, "work", 4) != 0) {
                error("msg head flag error");
                handler->remove(socket);
                return;
            }
            if (msg_head.len >= uint32_t(recv_buffer_size)) {
                error("recv msg body len: %d, large than recv_buff_size: %d", msg_head.len, recv_buffer_size);
                handler->remove(socket);
                return;
            }

            char buf[recv_buffer_size];
            memset(buf, 0, recv_buffer_size);
            //接收消息体
            len = socket->recv(buf, recv_buffer_size);
            if (len == -1) {
                error("socket recv,errno=%d errstr=%s", errno, strerror(errno));
                handler->remove(socket);
                return;
            }
            if (len != (int) msg_head.len) {
                error("recv msg body error length: %d, body: %s, errno: %d", len, buf, errno);
                handler->remove(socket);
                return;
            }

            info("recv msg body len: %d , msg data : %s", len, buf);

            std::ostringstream oss;
            oss << (int) msg_head.cmd;
            const std::string work = oss.str();
            const std::string intput = buf;
            std::string output;

            Singleton<Workflow>::instance()->run(work, intput, output);
            if (output.empty())
                output = "no data";
            socket->send(output.c_str(), (int) output.length());
            handler->attach(socket);
        }

        void WorkTask::destroy() {
            debug("work job destroy");
            delete this;
        }
    } // task
}