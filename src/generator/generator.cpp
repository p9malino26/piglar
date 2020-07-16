#include <iostream>
#include "../RoadMap.h"
#include "../GLMIncludes.h"
#include "../Random.h"
#include "../util/printVar.h"
#include "generator.h"

#define CONSTANT(EXPR) \
static constexpr EXPR;

namespace Generator {

    glm::vec2i generateTree(RoadMap& roadmap, const glm::vec2i& startpos, const TreeGenParams& params)
    {
        std::cout << "Generate tree started\n";
        assert(!roadmap.isPositionOutside(startpos));

        int mainRoadLength = Random::randInt(params.mainRoadLengthRange.first, params.mainRoadLengthRange.second);
        printf("Main road length: %d\n", mainRoadLength);
        glm::vec2i endPos = startpos;
        endPos.y += mainRoadLength - 1;
        assert(!roadmap.isPositionOutside(endPos));


        //for initial line:
        roadmap.setLine(startpos, CompassDirection::NORTH, mainRoadLength, true);

        auto genBranch = [&roadmap, &params](bool direction, const glm::vec2i& pos) -> int{

            int linelength = Random::randInt(params.branchRoadLengthRange.first, params.branchRoadLengthRange.second); // branch length
            auto startPos = pos;
            startPos.x += direction ? 1 : -1;
            roadmap.setLine(startPos, direction ? CompassDirection::EAST : CompassDirection::WEST, linelength, 1);
            return linelength;

        };

        int maxLBranchLength = 0, maxRBranchLength = 0;
        //for branches:
        for (glm::vec2i pos = startpos; pos.y <= endPos.y ;)
        {
            std::cout << "\nAt position " << pos.y << std::endl;
            int junctionChoice = Random::randInt(0,2);
            /*
                0: left
                1: right
                2: both left and right
            */
            if (junctionChoice == 0 || junctionChoice == 2) {// left
                int branchLength = genBranch(0, pos);
                maxLBranchLength = std::max(branchLength, maxLBranchLength);
                printf("Left branch length %d, max is now %d.\n", branchLength, maxLBranchLength);
            }

            if(junctionChoice == 1 || junctionChoice == 2) {// right
                int branchLength = genBranch(1, pos);
                maxRBranchLength = std::max(branchLength, maxRBranchLength);
                printf("Right branch length %d, max is now %d.\n", branchLength, maxRBranchLength);
            }

            //end steps:
            pos.y += Random::randInt(params.branchStepRange.first, params.branchStepRange.second);
        }
        std::cout << "Generate tree finished\n";


        return {maxLBranchLength + 1 + maxRBranchLength, mainRoadLength};

    }

    TreeGenerator::TreeGenerator(const TreeGenParams &params)
        :treeData(1 + 2 * params.branchRoadLengthRange.second, params.mainRoadLengthRange.second), params(params)
    {

    }

    glm::vec2i TreeGenerator::generate()
    {
        return generateTree(treeData, {params.branchRoadLengthRange.second, 0}, params);
    }

    void TreeGenerator::writeToMap(glm::vec2i startPos, RoadMap &roadMap, bool orientation)
    {
        std::cout << "Not implemented yet\n";
    }

}


