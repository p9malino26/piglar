#pragma once
#include <memory>

class TileMap;
class SquarePlayer;

namespace Generator { class RoadMapGen; }

class Scene
{
    friend class SceneRenderer;
    static constexpr int width = 100;
    static constexpr int height = 100;

    std::unique_ptr<TileMap> roadMap;
    std::unique_ptr<SquarePlayer> player;
    std::unique_ptr<SquarePlayer> chaser;

    std::unique_ptr<Generator::RoadMapGen> roadMapGen;

public:
    Scene();
    void update();
    inline const TileMap* getRoadMap() const { return roadMap.get(); }
    inline TileMap* getRoadMap() {return roadMap.get();}

    ~Scene();

    friend class SceneRenderer;
};
