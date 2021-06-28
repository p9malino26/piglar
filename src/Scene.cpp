#include "RoadMap.h"
#include "Scene.h"
#include "Input.h"

#include "generator/RoadMapGen.h"
#include "MouseManager.h"
#include "TimeManager.h"

#include "SquarePlayer.h"
#include "util/compassVec.h"

#define PLAYER_SPEED 2.f

void moveEntityWithCollisionDetection(const RoadMap& roadMap, Entity& entity, const RealPos& posDelta);

Scene::Scene()
    :roadMap(new RoadMap(width, height)), roadMapGen(new Generator::RoadMapGen(roadMap.get())),
    player(new SquarePlayer(RealPos(0.f, 1.f)))
{
    roadMapGen->generate();
}

RealPos getCollisionResolutionDelta(const RoadMap& tileMap, Entity& entity, const RealPos& initialDelta);

void Scene::update()
{
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

    if (Input::get()->getKeyEvent(GLFW_KEY_K) == GLFW_PRESS) {
        std::cout << "Current position: " << player->getPos() << std::endl;
        std::cout << "Collision resolution delta:" << getCollisionResolutionDelta(*roadMap, *player, RealPos(0)) << std::endl;
    }

    //move player

    glm::vec2 unit(0.f, 0.f);
    if(Input::get()->keyInfo(GLFW_KEY_W, GLFW_PRESS))
        unit += NORTH_VEC;
    if(Input::get()->keyInfo(GLFW_KEY_S, GLFW_PRESS))
        unit += SOUTH_VEC;
    if(Input::get()->keyInfo(GLFW_KEY_D, GLFW_PRESS))
        unit += EAST_VEC;
    if(Input::get()->keyInfo(GLFW_KEY_A, GLFW_PRESS))
        unit += WEST_VEC;

    auto initialDelta = unit * TimeManager::get()->deltaTime() * PLAYER_SPEED;

    player->changePos(getCollisionResolutionDelta(*roadMap, *player, initialDelta));
    //player->changePos(initialDelta);
}

Scene::~Scene(){
}
