#pragma once

#include "Application.h"

#include <memory>

class Camera;
class CameraManager;
class MouseManager;
class SceneRenderer;
class GameConfig;
class Scene;
class Renderer;
class TextManager;
class FTLabel;

class Game: public Application
{
    std::unique_ptr<Camera> camera;
    std::unique_ptr<CameraManager> cameraManager;

    std::unique_ptr<Scene> scene;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<SceneRenderer> sceneRenderer;

    std::unique_ptr<MouseManager> mouseManager;

    std::unique_ptr<TextManager> textManager;
    std::unique_ptr<FTLabel> timerLabel;
    std::unique_ptr<FTLabel> pigsLabel;

    void processFrame() override;
public:
    explicit Game(const GameConfig& config, unsigned int seed);
    ~Game();
};
