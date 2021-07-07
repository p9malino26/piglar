#pragma once
#include <memory>
#include <vector>
#include "util/singleton.h"
#include "vectors.h"

class TileMap;
class SquarePlayer;
class Player;
class Pig;

namespace Generator { class RoadMapGen; }

class Scene: public Singleton
{
    friend class SceneRenderer;
    static constexpr int width = 100;
    static constexpr int height = 100;

    std::unique_ptr<TileMap> roadMap;
    std::unique_ptr<Player> player;
    std::vector<Pig> pigs;

    std::unique_ptr<Generator::RoadMapGen> roadMapGen;
    //inline SquarePlayer& getPlayer() {return *player; }
    //inline std::vector<SquarePlayer>& getPigs() {return static_cast<std::vector<SquarePlayer>&>(pigs);}

    Scene();
public:
    void update();
    inline const TileMap* getRoadMap() const { return roadMap.get(); }
    inline TileMap* getRoadMap() {return roadMap.get();}
    const RealPos& getPlayerPos();

    ~Scene();

    friend class SceneRenderer;

SINGLETON(Scene)
    static void init() {instance = new Scene();}
};
