#include "Game.h"

#include "Input.h"
#include "RoadMap.h"

Game::Game()
    :Application("Piglar!!", 800, 600), renderer(&scene), cameraManager(&camera), mouseManager(&display, &camera)
{}

void Game::processFrame()
{
    cameraManager.update();
    scene.update();

    if (Input::mouseHasClicked()) {
        glm::vec2 mouseWorldPos = mouseManager.getWorldMousePos();
        glm::vec2i intMouseWorldPos = glm::vec2i((int)mouseWorldPos.x, (int)mouseWorldPos.y);
        scene.getRoadMap()->toggleFieldState(intMouseWorldPos);
    }
    renderer(camera.getViewMatrix(), display.getProjectionMatrix());
}
