#pragma once
#include <memory>
#include <vector>
#include "util/singleton.h"
#include "vectors.h"

class TileMap;
class Player;
class Pig;
class Truck;

namespace Generator { class RoadMapGen; class TreeGenParams;}
using namespace Generator;

class MechanicsConfig;


class Scene: public Singleton
{
    friend class SceneRenderer;


    std::unique_ptr<TileMap> roadMap;
    std::unique_ptr<Player> player;
    std::unique_ptr<Truck> truck;
    std::vector<Pig> pigs;

    std::unique_ptr<Generator::RoadMapGen> roadMapGen;

    bool m_won = false;
    //inline SquarePlayer& getPlayer() {return *player; }
    //inline std::vector<SquarePlayer>& getPigs() {return static_cast<std::vector<SquarePlayer>&>(pigs);}

    Scene(const MechanicsConfig &mechanicsConfig, const TreeGenParams &genConfig);
public:
    void update();
    void updateGame();
    inline const TileMap* getRoadMap() const { return roadMap.get(); }
    inline TileMap* getRoadMap() {return roadMap.get();}
    inline bool isWon() const {return m_won; }
    const RealPos& getPlayerPos();

    ~Scene();

    friend class SceneRenderer;

SINGLETON(Scene)
    static void init(const MechanicsConfig &mechanicsConfig, const TreeGenParams &genConfig) {instance = new Scene(mechanicsConfig, genConfig);}
};
