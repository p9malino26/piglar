#pragma once

#include <memory>

#include "../GLMIncludes.h"

class RoadMap;
struct TreeGenData;

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
        glm::vec2i generate();
        void writeTo(RoadMap& roadMap, glm::vec2i startPos, bool orientation);


        std::unique_ptr<RoadMap> treeData;
        ~TreeGenerator();
    private:
        TreeGenParams params;
        std::unique_ptr<TreeGenData> lastGenData;
    };
}


