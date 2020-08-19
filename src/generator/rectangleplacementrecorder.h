#pragma once

#include <list>

#include "../GLMIncludes.h"
#include "../util/line.h"

namespace Generator {

    struct ClosestPointInfo {
        glm::vec2i pos;
        int spaceInfo[4]; //north, east, south, west
    };

    class RectanglePlacementRecorder
    {        
    public:
        std::list<Line> lines;

        RectanglePlacementRecorder();

        //api
        void placeRectangle(const glm::vec2i& pos, const glm::vec2i& dims);
        void seclude(const glm::vec2i& pos);
        ClosestPointInfo getClosestPoint();
        ~RectanglePlacementRecorder();
    };
}

