#include "Camera.h"

#include "Input.h"
#include "TimeManager.h"

Camera::Camera()
:zoom(0.2f), speed(3.5f), zoomSpeed(0.01f)
{
    
}

void Camera::update()
{
    float distanceMoved = speed * TimeManager::deltaTime();
    if(Input::keyInfo(GLFW_KEY_UP, GLFW_PRESS))
        changeYpos(distanceMoved);
    if(Input::keyInfo(GLFW_KEY_DOWN, GLFW_PRESS))
        changeYpos(-distanceMoved);
    if(Input::keyInfo(GLFW_KEY_RIGHT, GLFW_PRESS))
        changeXpos(distanceMoved);
    if(Input::keyInfo(GLFW_KEY_LEFT, GLFW_PRESS))
        changeXpos(-distanceMoved);

    zoom += Input::yScrollDelta() * zoomSpeed;
    if (zoom > 0.8f) zoom = 0.8f;
    if (zoom < 0.01f) zoom = 0.01f;

}

glm::mat4 Camera::getViewMatrix() const
{
    glm::mat4 view(1.0f);
    view = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));
    view = glm::translate(view, glm::vec3(-position, 0.0f));
    return view;
}
