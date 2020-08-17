#pragma once

#include <glad/glad.h>

#include "Application.h"
#include "MouseManager.h"

#include <memory>

class CameraManager;
class SceneRenderer;
class Scene;

class Game: public Application
{
    std::unique_ptr<Camera> camera;
    std::unique_ptr<CameraManager> cameraManager;

    std::unique_ptr<Scene> scene;
    std::unique_ptr<SceneRenderer> renderer;

    MouseManager mouseManager;

    void processFrame() override;
public:
    Game();
    ~Game();
};

