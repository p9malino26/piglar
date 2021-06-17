#pragma once
#include <memory>

class RoadMap;

namespace Generator { class RoadMapGen; }

class Scene
{
    friend class SceneRenderer;
    static constexpr int width = 100;
    static constexpr int height = 100;

    std::unique_ptr<RoadMap> roadMap;

public:
    Scene();
    void update();
    inline const RoadMap* getRoadMap() const { return roadMap.get(); }
    inline RoadMap* getRoadMap() {return roadMap.get();}

    ~Scene();

    friend class SceneRenderer;
};
