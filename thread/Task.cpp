//
// Created by cepher on 5/8/23.
//

#include "Task.h"
#include "AutoLock.h"

using namespace crab::thread;

Task::Task():m_data(nullptr) {

}

Task::Task(void *data):m_data(data) {

}

Task::~Task() = default;

void *Task::get_data() {
    AutoLock lock(&m_mutex);
    return m_data;
}

void Task::set_data(void *data) {
AutoLock lock(&m_mutex);
    m_data = data;
}
