#pragma once
#include <memory>

class RoadMap;
namespace Generator {
    class RectanglePlacementRecorder;

}

class Scene
{
    static constexpr int width = 100;
    static constexpr int height = 100;

    std::unique_ptr<RoadMap> roadMap;
    Generator::RectanglePlacementRecorder* rpr;

public:
    Scene();
    void update();
    inline const RoadMap* getRoadMap() const { return roadMap.get(); }
    inline RoadMap* getRoadMap() {return roadMap.get();}
    /*inline auto getRectangePlacementStatus()
    {
        return rpr.;
    }*/
    ~Scene();

    friend class SceneRenderer;
private:
    void generateRoadMap() ;
};
