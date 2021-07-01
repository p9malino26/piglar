#include "Game.h"

#include "Input.h"
#include "TileMap.h"
#include "Camera.h"
#include "CameraManager.h"
#include "Scene.h"
#include "SceneRenderer.h"
#include "Renderer.h"
#include "util/Random.h"

Game::Game()
    :Application("Piglar!!", 800, 600),
      camera(new Camera()),
      cameraManager(new CameraManager(camera.get())),
      scene(new Scene())
{
    Renderer::init(camera.get(), &display);
    sceneRenderer = std::make_unique<SceneRenderer>(scene.get());
    Random::init();
    MouseManager::init(&display, camera.get());
}

void Game::processFrame()
{
    cameraManager->update();
    scene->update();


    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    sceneRenderer->render();
}

Game::~Game()
{
    Renderer::del();
    Random::del();
    MouseManager::del();
}
