#pragma once
#include <memory>
#include <vector>
#include "util/singleton.h"
#include "vectors.h"

class TileMap;
class SquarePlayer;

namespace Generator { class RoadMapGen; }

class Scene: public Singleton
{
    friend class SceneRenderer;
    static constexpr int width = 100;
    static constexpr int height = 100;

    std::unique_ptr<TileMap> roadMap;
    std::unique_ptr<SquarePlayer> player;
    std::vector<SquarePlayer> pigs;

    std::unique_ptr<Generator::RoadMapGen> roadMapGen;


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
