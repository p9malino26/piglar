#pragma once

#include "GLMIncludes.h"

#include "Camera.h"

class CameraManager
{
    enum CameraMode {FOLLOW_PLAYER, DETACHED};
    //some constants
    static constexpr float followSpeed = 0.2f;
    static constexpr float moveSpeed = 4.2f;
    static constexpr float zoomSpeed = 5.0f;

    static constexpr float minZoom = 0.01f;
    static constexpr float maxZoom = 0.8f;
    
    static constexpr glm::vec2 initialPosition = glm::vec2(9.0f, 9.0f);

    Camera* camera;
    CameraMode cameraMode = FOLLOW_PLAYER;

public:
    CameraManager(Camera*);
    void update();
};