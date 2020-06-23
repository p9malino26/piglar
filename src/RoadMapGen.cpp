#include "RoadMapGen.h"

#include <algorithm>
#include "GLMIncludes.h"

#include "RoadMap.h"

RoadMapGen::RoadMapGen(RoadMap* roadMap)
    :roadMap(roadMap)
{
    
}

void RoadMapGen::generate()
{
    roadMap->setFieldState(glm::vec2i(2,3), RoadMap::ON);
}