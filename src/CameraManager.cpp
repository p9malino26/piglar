#include <GLFW/glfw3.h>

#include "CameraManager.h"
#include "TimeManager.h"
#include "Input.h"

CameraManager::CameraManager(Camera* camera)
    :camera(camera)
{
    camera->setZoom(0.1f);
}


void CameraManager::update()
{   
    Camera& camera = *this->camera; 
    float distanceMoved = speed * TimeManager::get()->deltaTime();

    if(Input::get()->keyInfo(GLFW_KEY_UP, GLFW_PRESS))
        camera.changeYpos(distanceMoved);
    if(Input::get()->keyInfo(GLFW_KEY_DOWN, GLFW_PRESS))
        camera.changeYpos(-distanceMoved);
    if(Input::get()->keyInfo(GLFW_KEY_RIGHT, GLFW_PRESS))
        camera.changeXpos(distanceMoved);
    if(Input::get()->keyInfo(GLFW_KEY_LEFT, GLFW_PRESS))
        camera.changeXpos(-distanceMoved);

    if(Input::get()->keyInfo(GLFW_KEY_R, GLFW_PRESS) )
    {
        camera.setPosition(glm::vec2(0.0f, 0.0f));
    }

    camera.changeZoom(Input::get()->yScrollDelta() * zoomSpeed * TimeManager::get()->deltaTime());
    
    camera.clampZoom(minZoom, maxZoom);

}