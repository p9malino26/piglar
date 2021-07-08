#pragma once
#include <memory>
#include <vector>
#include "util/singleton.h"
#include "vectors.h"

class TileMap;
class SquarePlayer;
class Player;
class Pig;

namespace Generator { class RoadMapGen; class TreeGenParams;}
using namespace Generator;

class MechanicsConfig;


class Scene: public Singleton
{
    friend class SceneRenderer;


    std::unique_ptr<TileMap> roadMap;
    std::unique_ptr<Player> player;
    std::vector<Pig> pigs;

    std::unique_ptr<Generator::RoadMapGen> roadMapGen;
    //inline SquarePlayer& getPlayer() {return *player; }
    //inline std::vector<SquarePlayer>& getPigs() {return static_cast<std::vector<SquarePlayer>&>(pigs);}

    Scene(const MechanicsConfig &mechanicsConfig, const TreeGenParams &genConfig);
public:
    void update();
    inline const TileMap* getRoadMap() const { return roadMap.get(); }
    inline TileMap* getRoadMap() {return roadMap.get();}
    const RealPos& getPlayerPos();

    ~Scene();

    friend class SceneRenderer;

SINGLETON(Scene)
    static void init(const MechanicsConfig &mechanicsConfig, const TreeGenParams &genConfig) {instance = new Scene(mechanicsConfig, genConfig);}
};
