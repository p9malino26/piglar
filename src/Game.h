#pragma once

#include "Application.h"
#include "MouseManager.h"

#include <memory>

class CameraManager;
class SceneRenderer;
class GameConfig;
class Scene;
class Renderer;

class Game: public Application
{
    std::unique_ptr<Camera> camera;
    std::unique_ptr<CameraManager> cameraManager;

    std::unique_ptr<Scene> scene;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<SceneRenderer> sceneRenderer;

    std::unique_ptr<MouseManager> mouseManager;

    void processFrame() override;
public:
    explicit Game(const GameConfig& config, unsigned int seed);
    ~Game();
};
