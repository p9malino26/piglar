#include <GLFW/glfw3.h>

#include "CameraManager.h"

#include "CameraConfig.h"
#include "Camera.h"
#include "TimeManager.h"
#include "Input.h"
#include "MouseManager.h"
#include "Game.h"
#include "Scene.h"

CameraManager::CameraManager(Camera* camera, const CameraConfig& config)
    : m_camera(camera), m_config(&config)
{
    m_camera->setZoom(config.initialZoom);
}


void CameraManager::update()
{
    Camera& m_camera = *this->m_camera;
    float distanceMoved = m_config->moveSpeed * TimeManager::get()->deltaTime();

    //update mode
    if (Input::get()->getKeyEvent(GLFW_KEY_C) == GLFW_PRESS && Game::get()->isCheatsEnabled()) {
        setMode(CameraMode(1 - (int) m_mode));
        std::cout << "Camera mode: " << m_mode << std::endl;
    }

    auto zoomDelta = Input::get()->yScrollDelta() * m_config->zoomSpeed * TimeManager::get()->deltaTime();
    switch (m_mode) {
        case FOLLOW_PLAYER:
            m_camera.changePosition((Scene::get()->getPlayerPos() - m_camera.getPosition()) * m_config->followSpeed);
            break;
        case DETACHED:
            if (zoomDelta != 0)
            {
                auto worldThen = MouseManager::get()->getWorldMousePos();
                m_camera.changeZoom(zoomDelta);
                auto worldNow = MouseManager::get()->getWorldMousePos();
                m_camera.changePosition(worldThen - worldNow);
            }

            if(Input::get()->keyInfo(GLFW_KEY_UP, GLFW_PRESS))
                m_camera.changeYpos(distanceMoved);
            if(Input::get()->keyInfo(GLFW_KEY_DOWN, GLFW_PRESS))
                m_camera.changeYpos(-distanceMoved);
            if(Input::get()->keyInfo(GLFW_KEY_RIGHT, GLFW_PRESS))
                m_camera.changeXpos(distanceMoved);
            if(Input::get()->keyInfo(GLFW_KEY_LEFT, GLFW_PRESS))
                m_camera.changeXpos(-distanceMoved);

            auto dragDelta = Input::get()->getDragDelta();
            m_camera.changePosition( MouseManager::get()->mouseToWorld(RealPos(0)) - MouseManager::get()->mouseToWorld(dragDelta));
            //auto mouseDelta = Input::get()->getMouseDelta();
            break;
    }

    m_camera.clampZoom(m_config->zoomRange.first, m_config->zoomRange.second);

}

void CameraManager::setMode(CameraManager::CameraMode mode) {
    m_mode = mode;
    if (mode == FOLLOW_PLAYER) {
        m_camera->setPosition(Scene::get()->getPlayerPos());
        m_camera->setZoom(m_config->initialZoom);
    }
}
