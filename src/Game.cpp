#include "Game.h"

#include "Input.h"
#include "TileMap.h"
#include "Camera.h"
#include "CameraManager.h"
#include "Scene.h"
#include "SceneRenderer.h"
#include "Renderer.h"
#include "util/Random.h"

#include "GameConfig.h"

Game::Game(const GameConfig& config, unsigned int seed)
    :Application("Piglar!!", 800, 600),
      camera(new Camera()),
      cameraManager(new CameraManager(camera.get(), *config.cameraConfig))
{
    Scene::init(*config.mechanicsConfig, *config.generatorConfig);
    Renderer::init(camera.get(), &display);
    sceneRenderer = std::make_unique<SceneRenderer>(Scene::get());
    Random::init(seed);
    MouseManager::init(&display, camera.get());
}

void Game::processFrame()
{
    cameraManager->update();
    Scene::get()->update();



    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    sceneRenderer->render();
}

Game::~Game()
{
    Scene::del();
    Renderer::del();
    Random::del();
    MouseManager::del();
}
