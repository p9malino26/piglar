#include "RoadMap.h"
#include "Scene.h"
#include "Input.h"

#include "generator/RoadMapGen.h"
#include "MouseManager.h"
#include "TimeManager.h"

#include "SquarePlayer.h"
#include "util/compassVec.h"


void moveEntityWithCollisionDetection(const RoadMap& roadMap, Entity& entity, const RealPos& posDelta);

Scene::Scene()
    :roadMap(new RoadMap(width, height)), roadMapGen(new Generator::RoadMapGen(roadMap.get())),
    player(new SquarePlayer())
{
    roadMapGen->generate();
}

void Scene::update()
{
    //roadmap click
    if (Input::mouseHasClicked()) {
        glm::vec2 mouseWorldPos = MouseManager::get()->getWorldMousePos();
        glm::vec2i intMouseWorldPos = glm::vec2i((int)mouseWorldPos.x, (int)mouseWorldPos.y);
        std::cout << "Mouse position: " << intMouseWorldPos << std::endl;

        if (Input::getKeyStatus(GLFW_KEY_K) == GLFW_PRESS)
            player->setPos(MouseManager::get()->getWorldMousePos());
        else
            roadMap->toggleFieldState(intMouseWorldPos);
    }


    //move player
    RealPos direction(0.f, 0.f);

    if(Input::keyInfo(GLFW_KEY_W, GLFW_PRESS))
        direction += NORTH_VEC;
    if(Input::keyInfo(GLFW_KEY_S, GLFW_PRESS))
        direction += SOUTH_VEC;
    if(Input::keyInfo(GLFW_KEY_D, GLFW_PRESS))
        direction += EAST_VEC;
    if(Input::keyInfo(GLFW_KEY_A, GLFW_PRESS))
        direction += WEST_VEC;

    RealPos posDelta = direction * (3.f * TimeManager::deltaTime());
    moveEntityWithCollisionDetection(*roadMap, *player, {posDelta.x, 0});
    moveEntityWithCollisionDetection(*roadMap, *player, {0, posDelta.y});
}

Scene::~Scene(){
}
