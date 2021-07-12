#pragma once

#include "Application.h"
#include "MouseManager.h"

#include <memory>

class CameraManager;
class SceneRenderer;
class GameConfig;

class Game: public Application
{
    std::unique_ptr<Camera> camera;
    std::unique_ptr<CameraManager> cameraManager;

    std::unique_ptr<SceneRenderer> sceneRenderer;

    void processFrame() override;
public:
    explicit Game(const GameConfig& config, unsigned int seed);
    ~Game();
};
