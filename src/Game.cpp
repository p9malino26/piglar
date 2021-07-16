#include "Game.h"
#include <glad/glad.h>

#include "opengl/Display.h"
#include "TileMap.h"
#include "Camera.h"
#include "CameraManager.h"
#include "MouseManager.h"
#include "Scene.h"
#include "SceneRenderer.h"
#include "Renderer.h"
#include "util/Random.h"
#include <GLFont/GLFont.h>
#include <GLFont/FTLabel.h>

#include "GameConfig.h"
#include "TextManager.h"


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

    //init fonts and labels
    std::shared_ptr<GLFont> glFont;
    glFont = std::make_shared<GLFont>("res/fonts/13_5Atom_Sans_Regular.ttf");
    const int FONT_SIZE = 48;

    textManager = std::make_unique<TextManager>(glFont);

    timerLabel = textManager->newLabel();
    timerLabel->setPosition(0, 0);

    pigsLabel = textManager->newLabel();
    pigsLabel->setPosition(0, 30);


}

std::string getTimeString(const std::chrono::system_clock::duration& duration);

void Game::processFrame()
{
    static bool justWon = false;
    cameraManager->update();
    scene->update();

    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //glBindVertexArray(0);
    //glUseProgram(0);
    sceneRenderer->render();
    timerLabel->setText(getTimeString(scene->getTimeDuration()));
    timerLabel->render();

    pigsLabel->setText(std::string("Pigs caught: ") + to_string(scene->getPigsCaughtCount()) + '/' + to_string(scene->getPigsCount()));
    pigsLabel->render();
}

Game::~Game()
{
    Random::del();
}
