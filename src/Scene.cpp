#include "MainTileMap.h"
#include "Scene.h"
#include "Input.h"

#include "generator/RoadMapGen.h"
#include "MouseManager.h"
#include "TimeManager.h"

#include "util/compassVec.h"
#include "util/rangeFor.h"
#include "tileMapUtil.h"
#include "util/Random.h"
#include "Pig.h"
#include "Player.h"
#include "Truck.h"
#include "MechanicsConfig.h"
#include "Game.h"

Scene* Scene::instance;

std::vector<RealPos> spawnEvenly(int width, int height, int count);

inline BoardPos getRandomSpawnPos(int w, int h) {return BoardPos(Random::get()->randInt(0,w - 1), Random::get()->randInt(0,h - 1)); }

Scene::Scene(const MechanicsConfig& mechanicsConfig, const TreeGenParams& genConfig)
    :roadMap(new MainTileMap(mechanicsConfig.tileMapSize, mechanicsConfig.tileMapSize)),
    player(new Player(mechanicsConfig.playerSpeed)), truck(new Truck), pigCount(mechanicsConfig.pigsCount)
{
    instance = this;
    Generator::generateTerrain(*roadMap, genConfig);

    static auto getRandomSpawnPos = [&] () {return getClosestPosWithRoad(*roadMap, ::getRandomSpawnPos(roadMap->getWidth(), roadMap->getHeight())); };
    player->setPos(getRandomSpawnPos());
    truck->setPos (getRandomSpawnPos());
    Pig::init(mechanicsConfig.pigToPlayerSpeedRatio, mechanicsConfig.pigDetectionRange);

    std::vector<RealPos> pigPosns = spawnEvenly(roadMap->getWidth(), roadMap->getHeight(), mechanicsConfig.pigsCount);
    pigs.reserve(pigCount);
    RANGE_FOR(i, 0, pigCount)
    {
        pigs.emplace_back(getClosestPosWithRoad(*roadMap, pigPosns[i]));
    }
    startTime = std::chrono::system_clock::now();
    //pigs.emplace_back(getClosestPosWithRoad(*roadMap, RealPos(2,2)));
}

RealPos getCollisionResolutionDelta(const TileMap& tileMap, Entity& entity, const RealPos& initialDelta);
bool entitiesTouch(const Entity& e1, const Entity& e2);

void Scene::update() {
    if (!m_won)
        updateGame();
}

void Scene::updateGame()
{
    float deltaTime = TimeManager::get() ->deltaTime();
    //roadmap click

    if (Game::get()->isCheatsEnabled()) {
        if (Input::get()->getKeyStatus(GLFW_KEY_K) == GLFW_PRESS)
            player->setPos(MouseManager::get()->getWorldMousePos());

        if (Input::get()->getKeyStatus(GLFW_KEY_T) == GLFW_PRESS)
            for (Pig &p: pigs) { p.setPos(player->getPos()); };
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
        player->move(playerMoveDir * deltaTime * player->getSpeed());
    }

    //check win
    bool won = true;
    for (Pig& pig: pigs)
    {
        pig.update();
        won &= entitiesTouch(pig, *truck);
        if (entitiesTouch(pig, *player))
        {
            caughtPigs.insert(&pig);
        }
        endTime = std::chrono::system_clock::now();
    }

    if (won) m_won = true;

}

//RealPos getSpawnPoint()

Scene::~Scene(){
}


