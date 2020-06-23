#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <GLFW/glfw3.h>

class TimeManager
{
private:
    static float _deltaTime;
    static float currentFrameTime;
    static float lastFrameTime;
public:
    inline static float time() { return currentFrameTime;};
    inline static float deltaTime() { return _deltaTime;}

    static void init() {lastFrameTime = glfwGetTime();}

    static void update()
    { 
        currentFrameTime = glfwGetTime();        
        _deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
    }


};

#endif