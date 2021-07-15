#include <glad/glad.h>
#include "Game.h"

#include "TileMap.h"
#include "Camera.h"
#include "CameraManager.h"
#include "Scene.h"
#include "SceneRenderer.h"
#include "Renderer.h"
#include "util/Random.h"
#include <GLFont/GLFont.h>
#include <GLFont/FTLabel.h>

#include "GameConfig.h"


Game::Game(const GameConfig& config, unsigned int seed)
    :Application("Piglar!!", 800, 600),
    mouseManager(new MouseManager()),
      camera(new Camera()),
      cameraManager(new CameraManager(camera.get(), *config.cameraConfig)),
    scene( new Scene(*config.mechanicsConfig, *config.generatorConfig)),
    renderer(new Renderer())
{
    Random::init(seed);

    camera->setPosition(scene->getPlayerPos());
    sceneRenderer = std::make_unique<SceneRenderer>(scene.get());

    std::shared_ptr<GLFont> glFont;
    glFont = std::make_shared<GLFont>("res/fonts/13_5Atom_Sans_Regular.ttf");
    winLabel = std::make_unique<FTLabel>(glFont,  Display::get()->width(), Display::get()->height(), "res/shaders");
    const int FONT_SIZE = 48;
    winLabel->setPixelSize(FONT_SIZE);
    winLabel->setPosition(Display::get()->width() / 2,Display::get()->height() - FONT_SIZE);
    winLabel->setIndentation(50);
    winLabel->setAlignment(FTLabel::FontFlags::CenterAligned);
    winLabel->setColor(0.89, 0.26, 0.3, 0.9);
}

void Game::processFrame()
{
    static bool justWon = false;
    cameraManager->update();
    scene->update();

    if (scene->isWon())
    {
        if (!justWon) {
            winLabel->setText("Time: " + to_string(scene->getTimeDuration()) + "s");
        }
        winLabel->render();
        justWon = true;
    }

    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //glBindVertexArray(0);
    //glUseProgram(0);
    sceneRenderer->render();
    winLabel->render();
}

Game::~Game()
{
    Random::del();
}
