#pragma once

#include <utility>

template<typename T>
class Singleton
{
    static T* instance;
public:
    template<typename ... Args>
    static void init(Args&&... args) {
        instance = new T(std::forward<Args>(args) ...);
    }

    static T* get()map
    {
        return instance;
    }

    static void del()
    {
        delete instance;
    }

    Singleton& operator =(Singleton&  other) = delete;
    Singleton& operator =(Singleton&& other) = delete;

protected:
    Singleton() = default;
    //virtual ~Singleton() = default;
};
