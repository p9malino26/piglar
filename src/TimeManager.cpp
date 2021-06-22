#include "TimeManager.h"

TimeManager* TimeManager::instance;
TimeManager::TimeManager()  {lastFrameTime = glfwGetTime();}

void TimeManager::init() {instance = new TimeManager(); }


void TimeManager::update()
{
    currentFrameTime = glfwGetTime();
    _deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
}
