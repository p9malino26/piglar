#include "RoadMap.h"
#include "Scene.h"
#include "Input.h"

#include "generator/RoadMapGen.h"
#include "MouseManager.h"
#include "TimeManager.h"

#include "SquarePlayer.h"
#include "util/compassVec.h"

#define PLAYER_SPEED 4.f
#define CHASER_SPEED 0.4F * PLAYER_SPEED

void moveEntityWithCollisionDetection(const TileMap& tileMap, Entity& entity, const RealPos& posDelta);


Scene::Scene()
    :roadMap(new TileMap(width, height)), roadMapGen(new Generator::RoadMapGen(roadMap.get())),
    player(new SquarePlayer(RealPos(0.f, 1.f))), chaser(new SquarePlayer(RealPos(0.f, 13.f)))
{
    roadMapGen->generate();
}

RealPos getCollisionResolutionDelta(const TileMap& tileMap, Entity& entity, const RealPos& initialDelta);

void Scene::update()
{
    float deltaTime = TimeManager::get() ->deltaTime();
    //roadmap click
    if (Input::get()->mouseHasClicked()) {
        glm::vec2 mouseWorldPos = MouseManager::get()->getWorldMousePos();
        glm::vec2i intMouseWorldPos = glm::vec2i((int)mouseWorldPos.x, (int)mouseWorldPos.y);
        std::cout << "Mouse position: " << intMouseWorldPos << std::endl;

        if (Input::get()->getKeyStatus(GLFW_KEY_K) == GLFW_PRESS)
            player->setPos(MouseManager::get()->getWorldMousePos());
        else
            roadMap->toggleFieldState(intMouseWorldPos);
    }

    //move player

    glm::vec2 playerMoveDir(0.f, 0.f);
    if(Input::get()->keyInfo(GLFW_KEY_W, GLFW_PRESS))
        playerMoveDir += NORTH_VEC;
    if(Input::get()->keyInfo(GLFW_KEY_S, GLFW_PRESS))
        playerMoveDir += SOUTH_VEC;
    if(Input::get()->keyInfo(GLFW_KEY_D, GLFW_PRESS))
        playerMoveDir += EAST_VEC;
    if(Input::get()->keyInfo(GLFW_KEY_A, GLFW_PRESS))
        playerMoveDir += WEST_VEC;

    if (playerMoveDir != RealPos(0.f,0.f)) {
        auto initialDelta = playerMoveDir * deltaTime * PLAYER_SPEED;
        player->changePos(getCollisionResolutionDelta(*roadMap, *player, initialDelta));
    }
    
    //move chaser
    auto chaserMoveDir = player->getPos() - chaser->getPos();
    auto chaserDelta = chaserMoveDir * CHASER_SPEED * deltaTime;
    chaser->changePos(getCollisionResolutionDelta(*roadMap, *chaser, chaserDelta));
}

Scene::~Scene(){
}
