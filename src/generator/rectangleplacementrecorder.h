#pragma once

#include <list>

struct Line;

namespace Generator {

    struct ClosestPointInfo {
        glm::vec2i pos;
        int spaceInfo[4]; //north, east, south, west
    };

    class RectanglePlacementRecorder
    {
    public:
        RectanglePlacementRecorder();

        //api
        void placeRectangle(const glm::vec2i& pos, const glm::vec2i& dims);
        void seclude(const glm::vec2i& pos);
        ClosestPointInfo getClosestPoint();
        ~RectanglePlacementRecorder();

        //for rendering
        inline const auto& getBoundaryLines()
        {
            return lines;
        }
    private:
        std::list<Line> lines;
    };
}

