#ifndef CAMERA_H
#define CAMERA_H

#include "util/vectors.h"
#include "util/singleton.h"

class Camera: public Singleton
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

    inline const glm::vec2& getPosition() {return position; }

    inline void setPosition(const glm::vec2& _position)
    {
        position = _position;
    }

    inline void changePosition(const glm::vec2& delta)
    {
        position += delta;
    }

    glm::mat4 getViewMatrix() const;

SINGLETON(Camera)
};

#endif
