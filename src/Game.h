#pragma once

#include <glad/glad.h>

#include "Application.h"
#include "Camera.h"
#include "CameraManager.h"
#include "MouseManager.h"

#include <memory>

class Renderer;
class Scene;

class Game: public Application
{
    Camera camera;
    CameraManager cameraManager;

    std::unique_ptr<Scene> scene;
    std::unique_ptr<Renderer> renderer;

    MouseManager mouseManager;

    void processFrame() override;
public:
    Game();
    ~Game();
};

