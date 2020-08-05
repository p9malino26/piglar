#ifndef SCENE_H
#define SCENE_H

#include <memory>

class RoadMap;

class Scene
{
public:
    Scene();
    void update();
    inline const RoadMap* getRoadMap() const { return roadMap.get(); }
    inline RoadMap* getRoadMap() {return roadMap.get();}
    ~Scene();
private:
    static constexpr int width = 100;
    static constexpr int height = 100;

    std::unique_ptr<RoadMap> roadMap;
};

#endif 
