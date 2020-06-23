#pragma once

#include "GLMIncludes.h"

#include "Camera.h"

class CameraManager
{
    //some constants
    static constexpr float speed = 3.5f;
    static constexpr float zoomSpeed = 5.0f;

    static constexpr float minZoom = 0.01f;
    static constexpr float maxZoom = 0.8f;
    
    static constexpr glm::vec2 initialPosition = glm::vec2(9.0f, 9.0f);

    Camera* camera;

public:
    CameraManager(Camera*);
    void update();
};