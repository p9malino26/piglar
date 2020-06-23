#include "Sprite.h"

#include "Input.h"
#include "TimeManager.h"

Sprite::Sprite()
    :width(0.7f), speed(4.0f)
{

}

void Sprite::update()
{
    float distanceMoved = TimeManager::deltaTime() * speed;
    if(Input::keyInfo(GLFW_KEY_W, GLFW_PRESS))
        changeYpos(distanceMoved);
    if(Input::keyInfo(GLFW_KEY_S, GLFW_PRESS))
        changeYpos(-distanceMoved);
    if(Input::keyInfo(GLFW_KEY_D, GLFW_PRESS))
        changeXpos(distanceMoved);
    if(Input::keyInfo(GLFW_KEY_A, GLFW_PRESS))
        changeXpos(-distanceMoved);

}