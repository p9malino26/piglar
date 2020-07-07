#include "Game.h"

#include "Input.h"

Game::Game()
    :Application("Piglar!!", 800, 600), renderer(&scene), cameraManager(&camera), mouseManager(&display, &camera)
{}

void Game::processFrame()
{
    cameraManager.update();
    scene.update();

    renderer(camera.getViewMatrix(), display.getProjectionMatrix());
}
