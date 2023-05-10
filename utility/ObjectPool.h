//
// Created by cepher on 5/10/23.
//


#ifndef CRAB_HPF_OBJECTPOOL_H
#define CRAB_HPF_OBJECTPOOL_H


#include <list>
#include "../thread/Mutex.h"
#include "../thread/AutoLock.h"

using namespace crab::thread;

namespace crab {
    template<class T>
    class ObjectPool {
    public:
        ObjectPool();

        ~ObjectPool();

        void init(int max);
        //从池中取
        T *allocate();
        //放回池中
        void release(T *ptr);

    private:
        std::list<T *> m_pool;
        Mutex m_mutex;
    };

    template<class T>
    ObjectPool<T>::ObjectPool() = default;

    template<class T>
    ObjectPool<T>::~ObjectPool() {
        AutoLock lock(&m_mutex);
        for (auto it = m_pool.begin(); it != m_pool.end(); it++)
            if (*it != nullptr)
                delete *it;
        m_pool.clear();
    }

    template<typename T>
    void ObjectPool<T>::init(int max) {
        AutoLock lock(&m_mutex);
        for (int i = 0; i < max; i++) {
            T *p = new T();
            m_pool.push_back(p);
        }
    }

    template<typename T>
    T *ObjectPool<T>::allocate() {
        AutoLock lock(&m_mutex);
        if (m_pool.empty())
            return nullptr;
        auto p = m_pool.front();
        m_pool.pop_front();
        return p;
    }

    template <typename T>
    void ObjectPool<T>::release(T *ptr) {
        AutoLock lock(&m_mutex);
        m_pool.push_back(ptr);
    }

}
#endif //CRAB_HPF_OBJECTPOOL_H