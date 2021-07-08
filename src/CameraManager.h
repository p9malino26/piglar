#pragma once

#include "GLMIncludes.h"

class Camera;
class CameraConfig;

class CameraManager
{
    enum CameraMode {FOLLOW_PLAYER, DETACHED};

    const CameraConfig* config;
    Camera* camera;
    CameraMode cameraMode = FOLLOW_PLAYER;

public:
    CameraManager(Camera*, const CameraConfig& config);
    void update();
};