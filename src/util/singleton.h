#pragma once

#include <utility>

class Singleton
{
    Singleton& operator =(Singleton&  other) = delete;
    Singleton& operator =(Singleton&& other) = delete;

protected:
    Singleton() = default;
    //virtual ~Singleton() = default;
};

#define SINGLETON(T) \
private:\
static T* instance;\
public:\
static T* get()\
{\
return instance;\
}\
static void del()\
{\
    delete instance;\
}
