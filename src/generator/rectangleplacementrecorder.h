#pragma once

#include <list>

#include "../GLMIncludes.h"
#include "../util/line.h"

namespace Generator {

    struct ClosestPointInfo {
        glm::vec2i pos;
        CompassDirection normalDirection;
        int leftSpace, rightSpace;
    };

    class RectanglePlacementRecorder
    {
        glm::vec2i origin;
    public:
        std::list<Line> lines;

        RectanglePlacementRecorder(const glm::vec2i& origin);

        //api
        void placeRectangle(const glm::vec2i& pos, const glm::vec2i& dims);
        void seclude(const glm::vec2i& pos);
        ClosestPointInfo getClosestPoint();
        ~RectanglePlacementRecorder();
    };
}

