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
    mouseManager(new MouseManager()),
      camera(new Camera()),
      cameraManager(new CameraManager(camera.get(), *config.cameraConfig)),
    scene( new Scene(*config.mechanicsConfig, *config.generatorConfig)),
    renderer(new Renderer())
{
    sceneRenderer = std::make_unique<SceneRenderer>(scene.get());
    Random::init(seed);
}

void Game::processFrame()
{
    static bool justWon = false;
    cameraManager->update();
    scene->update();

    if (scene->isWon() && !justWon)
    {
        std::cout << "Time: " << scene->getTimeDuration() << "s.\n";
        justWon = true;
    }
    
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    sceneRenderer->render();
}

Game::~Game()
{
    Random::del();
}
