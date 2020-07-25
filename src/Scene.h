#ifndef SCENE_H
#define SCENE_H

#include "Entities.h"
#include "RoadMap.h"
#include "RoadMapGen.h"

#include "generator/generator.h"

class Scene
{
public:
    Scene();
    void update();
    inline const RoadMap* getRoadMap() const { return &roadMap; }
    inline RoadMap* getRoadMap() {return &roadMap;}
private:
    static constexpr int width = 50;
    static constexpr int height = 50;

    RoadMap roadMap;
};

#endif 
