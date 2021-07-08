#include "Game.h"
#include "GameConfig.h"

#include "generator/TreeGenParams.h"
#include "MechanicsConfig.h"
#include "CameraConfig.h"

int main()
{
    auto treeGenParams = new Generator::TreeGenParams;
    treeGenParams->mainRoadLengthRange = {7,11};
    treeGenParams->branchRoadLengthRange = {5, 7};
    treeGenParams->branchStepRange = {2, 4};

    auto mechanicsConfig = new MechanicsConfig;
    mechanicsConfig->tileMapSize = 100;
    mechanicsConfig->playerSpeed = 7.f;
    mechanicsConfig->pigsCount = 20;
    mechanicsConfig->pigToPlayerSpeedRatio = 0.7f;

    auto cameraConfig = new CameraConfig;
    cameraConfig->followSpeed = 0.2f;
    cameraConfig->moveSpeed = 4.2f;
    cameraConfig->zoomSpeed = 5.0f;
    cameraConfig->zoomRange = {0.01f, 0.8f};


    GameConfig gameConfig;
    gameConfig.generatorConfig.reset(treeGenParams);
    gameConfig.cameraConfig.reset(cameraConfig);
    gameConfig.mechanicsConfig.reset(mechanicsConfig);

    Game game(gameConfig);
    game.runMainLoop();
}