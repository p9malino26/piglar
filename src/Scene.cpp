#include "TileMap.h"
#include "Scene.h"
#include "Input.h"

#include "generator/RoadMapGen.h"
#include "MouseManager.h"
#include "TimeManager.h"

#include "SquarePlayer.h"
#include "util/compassVec.h"
#include "util/rangeFor.h"
#include "tileMapUtil.h"

#define PLAYER_SPEED 4.f
#define CHASER_SPEED (0.7F * PLAYER_SPEED)
#define PIGS_COUNT 20
#define PIG_LINE_OF_SIGHT 7

void moveEntityWithCollisionDetection(const TileMap& tileMap, Entity& entity, const RealPos& posDelta);

std::vector<RealPos> spawnEvenly(int width, int height, int count);

Scene::Scene()
    :roadMap(new TileMap(width, height)), roadMapGen(new Generator::RoadMapGen(roadMap.get())),
    player(new SquarePlayer())
{
    roadMapGen->generate();

    player->setPos(getClosestPosWithRoad(*roadMap, RealPos(1.f, 1.f)));

    std::vector<RealPos> pigPosns = spawnEvenly(roadMap->getWidth(), roadMap->getHeight(), PIGS_COUNT);
    RANGE_FOR(i, 0, PIGS_COUNT)
    {
        pigs.emplace_back(getClosestPosWithRoad(*roadMap, pigPosns[i]));
    }
    //pigs.emplace_back(getClosestPosWithRoad(*roadMap, RealPos(2,2)));
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
        std::cout << "closest pos with road: " << getClosestPosWithRoad(*roadMap, intMouseWorldPos) << std::endl;

        if (Input::get()->getKeyStatus(GLFW_KEY_K) == GLFW_PRESS)
            player->setPos(MouseManager::get()->getWorldMousePos());
        //else
        //    roadMap->toggleFieldState(intMouseWorldPos);
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
    
    auto moveDistance = CHASER_SPEED * deltaTime;
    //move chaser
    auto movePig = [this, moveDistance] (auto& pig)
    {
        auto pig2player = player->getPos() - pig.getPos();
        float distance = glm::length(pig2player);
        if (distance > PIG_LINE_OF_SIGHT || distance < 0.1) return;
        auto pig2playerU = glm::normalize(pig2player);
        auto pigMove = getCollisionResolutionDelta(*roadMap, pig, pig2playerU * moveDistance);
        pig.changePos(pigMove);
    };

    for (auto& pig: pigs) movePig(pig);

}

//RealPos getSpawnPoint()

Scene::~Scene(){
}


