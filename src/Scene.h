#pragma once
#include <memory>

class RoadMap;
class SquarePlayer;

namespace Generator { class RoadMapGen; }

class Scene
{
    friend class SceneRenderer;
    static constexpr int width = 100;
    static constexpr int height = 100;

    std::unique_ptr<RoadMap> roadMap;
    std::unique_ptr<SquarePlayer> player;

    std::unique_ptr<Generator::RoadMapGen> roadMapGen;

public:
    Scene();
    void update();
    inline const RoadMap* getRoadMap() const { return roadMap.get(); }
    inline RoadMap* getRoadMap() {return roadMap.get();}

    ~Scene();

    friend class SceneRenderer;
};
