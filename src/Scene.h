#ifndef SCENE_H
#define SCENE_H

#include "Entities.h"
#include "RoadMap.h"

class Scene
{
    friend class Renderer;
    void update();
private:
    Player player;
    RoadMap roadMap;
};

#endif 