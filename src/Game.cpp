#include "Game.h"

#include "Input.h"
#include "RoadMap.h"
#include "Camera.h"
#include "CameraManager.h"
#include "Scene.h"
#include "SceneRenderer.h"
#include "Renderer.h"


Game::Game()
    :Application("Piglar!!", 800, 600),
      camera(new Camera()),
      cameraManager(new CameraManager(camera.get())),
      scene(new Scene()),
      renderer(new SceneRenderer(scene.get())),
      mouseManager(&display, camera.get())
{
    Renderer::init(camera.get(), &display);
}

void Game::processFrame()
{
    cameraManager->update();
    scene->update();


    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    renderer->render();
}

Game::~Game()
{
    Renderer::destroy();
}
