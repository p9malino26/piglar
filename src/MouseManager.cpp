#include "MouseManager.h"
#include "Input.h"

#include "opengl/Display.h"
#include "Camera.h"

MouseManager* MouseManager::instance;

MouseManager::MouseManager(Display* display, Camera* camera)
    :display(display), camera(camera)
{
    instance = this;
}


glm::vec2 MouseManager::getWorldMousePos()
{
    return mouseToWorld(Input::get()->getMousePos());
}


void MouseManager::init(Display * display, Camera * camera) {
    instance = new MouseManager(display, camera);
}

void MouseManager::update() {

    //std::cout << Input::get()->getMousePos() - Input::get()->lastMousePos << std::endl;
    //auto cameraDelta = mouseToWorld(dragDelta);
    //camera->changePosition(cameraDelta);
}

RealPos MouseManager::mouseToWorld(RealPos mouseVec) {
    const glm::mat4& pixel = display->getPixelMatrix();
    const glm::mat4& proj = display->getProjectionMatrix();
    const glm::mat4& view = camera->getViewMatrix();
    glm::mat4 worldToScreen = pixel * proj * view;
    glm::mat4 screenToWorld = glm::inverse(worldToScreen);
    glm::vec4 mousePos = glm::vec4(mouseVec, 0.0f, 1.0f);
    return screenToWorld * mousePos;
}
