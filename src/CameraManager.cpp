#include <GLFW/glfw3.h>

#include "CameraManager.h"
#include "TimeManager.h"
#include "Input.h"
#include "MouseManager.h"
#include "Scene.h"

CameraManager::CameraManager(Camera* camera)
    :camera(camera)
{
    camera->setZoom(0.1f);
}


void CameraManager::update()
{
    Camera& camera = *this->camera;
    float distanceMoved = moveSpeed * TimeManager::get()->deltaTime();

    //update mode
    if (Input::get()->getKeyEvent(GLFW_KEY_C) == GLFW_PRESS) {
        cameraMode = CameraMode(1 - (int) cameraMode);
        std::cout << "Camera mode: " << cameraMode << std::endl;
    }

    auto zoomDelta = Input::get()->yScrollDelta() * zoomSpeed * TimeManager::get()->deltaTime();
    switch (cameraMode) {
        case FOLLOW_PLAYER:
            camera.changePosition((Scene::get()->getPlayerPos() - camera.getPosition()) * followSpeed);
            camera.changeZoom(zoomDelta);
            break;
        case DETACHED:
            if (zoomDelta != 0)
            {
                auto worldThen = MouseManager::get()->getWorldMousePos();
                camera.changeZoom(zoomDelta);
                auto worldNow = MouseManager::get()->getWorldMousePos();
                camera.changePosition(worldThen - worldNow);
            }

            if(Input::get()->keyInfo(GLFW_KEY_UP, GLFW_PRESS))
                camera.changeYpos(distanceMoved);
            if(Input::get()->keyInfo(GLFW_KEY_DOWN, GLFW_PRESS))
                camera.changeYpos(-distanceMoved);
            if(Input::get()->keyInfo(GLFW_KEY_RIGHT, GLFW_PRESS))
                camera.changeXpos(distanceMoved);
            if(Input::get()->keyInfo(GLFW_KEY_LEFT, GLFW_PRESS))
                camera.changeXpos(-distanceMoved);

            auto dragDelta = Input::get()->getDragDelta();
            camera.changePosition( MouseManager::get()->mouseToWorld(RealPos(0)) - MouseManager::get()->mouseToWorld(dragDelta));
            //auto mouseDelta = Input::get()->getMouseDelta();
            break;
    }


    //camera.changeZoom(Input::get()->yScrollDelta() ;



    //make camera follow player

    camera.clampZoom(minZoom, maxZoom);

}