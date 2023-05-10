//
// Created by cepher on 5/8/23.
//
#ifndef CRAB_HPF_SINGLETON_H
#define CRAB_HPF_SINGLETON_H
namespace crab {
    template<class T>
    class Singleton {

    public:
        static T *instance() {
            if (m_instance == nullptr)
                m_instance = new T();
            return m_instance;
        }

    private:
        Singleton() {}

        Singleton(const Singleton<T> &) = default;

        Singleton<T> &operator=(const Singleton<T> &) {}

        ~Singleton() = default;

    private:
        static T *m_instance;

    };

    template<class T>
    T *Singleton<T>::m_instance = nullptr;

}
#endif //CRAB_HPF_SINGLETON_H
