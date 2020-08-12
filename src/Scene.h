#pragma once
#include <memory>

class RoadMap;
class RectanglePlacementRecorder;

class Scene
{
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

    friend class Renderer;
private:
    static constexpr int width = 100;
    static constexpr int height = 100;

    std::unique_ptr<RoadMap> roadMap;
    RectanglePlacementRecorder* rpr;
};
