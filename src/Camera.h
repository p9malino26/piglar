#ifndef CAMERA_H
#define CAMERA_H

#include "GLMIncludes.h"

class Camera
{
    float zoom;
    float speed;
    float zoomSpeed;
    glm::vec2 position;

public:

    Camera();
    void update();
    inline void changeXpos(float delta)
    {
        position.x += delta;
    }

    inline void changeYpos(float delta)
    {
        position.y += delta;
    }
    inline void changeZoom(float zoomDelta)
    {
        zoom += zoomDelta;
    }

    inline void setPosition(const glm::vec2& _position)
    {
        position = _position;
    }



    glm::mat4 getViewMatrix() const;

};

#endif
