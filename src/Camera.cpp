#include <algorithm>
#include <cmath>

#include "Camera.h"

Camera* Camera::instance;

Camera::Camera()
    :position(0.0f, 0.0f), zoom(1.0f)
{
    instance = this;
}

Camera::Camera(const glm::vec2& position, float zoom)
    :position(position), zoom(zoom)
{
    
}

glm::mat4 Camera::getViewMatrix() const
{
    glm::mat4 view(1.0f);
    view = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));
    view = glm::translate(view, glm::vec3(-position, 0.0f));
    return view;
}

void Camera::changeZoom(float zoomDelta)
{
    zoom *= std::exp(zoomDelta);
}


void Camera::clampZoom(float low, float high)
{
    zoom = std::clamp(zoom, low, high);
}
