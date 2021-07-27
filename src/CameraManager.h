#pragma once

#include "util/vectors.h"

class Camera;
class CameraConfig;

class CameraManager
{
    enum CameraMode {FOLLOW_PLAYER, DETACHED};

    const CameraConfig* m_config;
    Camera* m_camera;
    CameraMode m_mode = FOLLOW_PLAYER;

public:
    CameraManager(Camera*, const CameraConfig& config);
    void update();
    void setMode(CameraMode mode);
};