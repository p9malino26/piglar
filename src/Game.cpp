#include "Game.h"

#include "Input.h"
#include "RoadMap.h"

#include "Renderer.h"

Game::Game()
    :Application("Piglar!!", 800, 600), cameraManager(&camera), scene(new Scene), renderer(new Renderer(scene.get())), mouseManager(&display, &camera)
{}

void Game::processFrame()
{
    cameraManager.update();
    scene->update();

    if (Input::mouseHasClicked()) {
        glm::vec2 mouseWorldPos = mouseManager.getWorldMousePos();
        glm::vec2i intMouseWorldPos = glm::vec2i((int)mouseWorldPos.x, (int)mouseWorldPos.y);
        scene->getRoadMap()->toggleFieldState(intMouseWorldPos);
    }
    (*renderer)(camera.getViewMatrix(), display.getProjectionMatrix());
}

Game::~Game() = default;
