#pragma once

#include "../GLMIncludes.h"

namespace Generator {

    struct ClosestPointInfo {
        glm::vec2i pos;
        int spaceWidth;
    };

    class RectanglePlacementRecorder
    {
    public:
        RectanglePlacementRecorder();

        //api
        void placeRectangle(const glm::vec2i& pos, int width, int height);
        ClosestPointInfo getClosestPoint();
    };
}

