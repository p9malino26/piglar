#pragma once

#include <glad/glad.h>

#include "Application.h"
#include "Camera.h"
#include "CameraManager.h"
#include "Scene.h"
#include "Renderer.h"
#include "MouseManager.h"



class Game: public Application
{
    Camera camera;
    CameraManager cameraManager;
    Scene scene;

    Renderer renderer;

    MouseManager mouseManager;

    void processFrame() override;
public:
    Game();
};

