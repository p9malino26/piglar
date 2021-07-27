#pragma once
#include <memory>
#include <vector>
#include <chrono>
#include <set>
#include "../util/singleton.h"
#include "../util/vectors.h"

class TileMap;
class Player;
class Pig;
class Truck;

namespace Generator { class RoadMapGen; class TreeGenParams;}
using namespace Generator;

class MechanicsConfig;

typedef decltype(std::chrono::system_clock::now()) TimePoint;

class Scene: public Singleton
{
    friend class SceneRenderer;

    int pigCount;

    std::unique_ptr<TileMap> roadMap;
    std::unique_ptr<Player> player;
    std::unique_ptr<Truck> truck;
    std::vector<Pig> pigs;

    bool m_won = false;
    TimePoint startTime;
    TimePoint endTime;

    std::set<void*> caughtPigs;
    //inline SquarePlayer& getPlayer() {return *player; }
    //inline std::vector<SquarePlayer>& getPigs() {return static_cast<std::vector<SquarePlayer>&>(pigs);}

public:
    Scene(const MechanicsConfig &mechanicsConfig, const TreeGenParams &genConfig);
    void update();
    void updateGame();
    inline const TileMap* getRoadMap() const { return roadMap.get(); }
    inline TileMap* getRoadMap() {return roadMap.get();}
    inline bool isWon() const {return m_won; }
    inline int getPigsCount() {return pigCount; }
    inline int getPigsCaughtCount() { return caughtPigs.size();}
    const RealPos& getPlayerPos();
    inline std::chrono::system_clock::duration getTimeDuration() { return endTime - startTime; }
    ~Scene();
    friend class SceneRenderer;

SINGLETON(Scene)
};
