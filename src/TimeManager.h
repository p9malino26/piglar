#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <GLFW/glfw3.h>
#include "util/singleton.h"

class TimeManager: public Singleton
{
private:
    float _deltaTime;
    float currentFrameTime;
    float lastFrameTime;
    TimeManager();
public:
    inline float time() { return currentFrameTime;};
    inline float deltaTime() { return _deltaTime;}


    void update();

SINGLETON(TimeManager)
    static void init();

};

#endif