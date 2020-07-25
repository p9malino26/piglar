#pragma once

#include "../GLMIncludes.h"

class RoadMap;

namespace Generator {

    //structs
    struct TreeGenParams
    {
        std::pair<int, int> mainRoadLengthRange, branchRoadLengthRange, branchStepRange;
    };

    class TreeGenerator
    {
    public:

        //methods
        TreeGenerator(const TreeGenParams& params);
        /**
         * Prepares a tree inside. Returns the rectangular width and height of the tree
         */
        glm::vec2i generateAndWrite(const glm::vec2i& startPos, RoadMap& roadMap, bool orientation);
        void writeToMap(glm::vec2i startPos, RoadMap& roadMap, bool orientation);

        RoadMap treeData;
    private:
        TreeGenParams params;
    };
}


