#pragma once

#include "../GLMIncludes.h"

class RoadMap;

namespace Generator {

    //structs
    struct TreeGenParams
    {
        std::pair<int, int> mainRoadLengthRange, branchRoadLengthRange, branchStepRange;
    };
    glm::vec2i generateTree(RoadMap& roadmap, const glm::vec2i& startpos, const TreeGenParams& params);

    class TreeGenerator
    {
    public:

        //methods
        TreeGenerator(const TreeGenParams& params);
        /**
         * Prepares a tree inside. Returns the rectangular width and height of the tree
         */
        glm::vec2i generate();
        void writeToMap(glm::vec2i startPos, RoadMap& roadMap);

    private:
        RoadMap treeData;
        TreeGenParams params;
    };
}


