#ifndef SCENE_H
#define SCENE_H

#include "Entities.h"
#include "RoadMap.h"
#include "RoadMapGen.h"

#include "generator/generator.h"


#include <memory>

class Scene
{
public:
    Scene();
    void update();
    inline const RoadMap* getRoadMap() const { return &treeGen->treeData; }
    inline RoadMap* getRoadMap() {return &treeGen->treeData;}
private:
    static constexpr int width = 50;
    static constexpr int height = 50;

    std::unique_ptr<Generator::TreeGenerator> treeGen;

    RoadMap roadMap;
    RoadMapGen roadGenerator;
};

#endif 
