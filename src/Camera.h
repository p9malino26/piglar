#ifndef CAMERA_H
#define CAMERA_H

#include "GLMIncludes.h"

class Camera
{
    float zoom; // how much you are actually scaling
    glm::vec2 position;

public:
    Camera();
    Camera(const glm::vec2& position, float zoom);

    inline void changeXpos(float delta)
    {
        position.x += delta;
    }

    inline void changeYpos(float delta)
    {
        position.y += delta;
    }
    inline void setZoom(float zoom) {this->zoom = zoom; }
    void changeZoom(float zoomDelta);

    void clampZoom(float low, float high);

    inline void setPosition(const glm::vec2& _position)
    {
        position = _position;
    }

    glm::mat4 getViewMatrix() const;


};

#endif
