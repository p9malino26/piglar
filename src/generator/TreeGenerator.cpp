#include <iostream>
#include "../RoadMap.h"
#include "../GLMIncludes.h"
#include "../util/Random.h"
#include "../util/printVar.h"
#include "treeGenData.h"
#include "TreeGenerator.h"

#define CONSTANT(EXPR) \
static constexpr EXPR;

namespace Generator {


    TreeGenData generateTree(RoadMap& roadmap, const glm::vec2i& startpos, const TreeGenParams& params)
    {
        std::cout << "Generate tree started\n";
        assert(!roadmap.isPositionOutside(startpos));

        int mainRoadLength = Random::get()->randInt(params.mainRoadLengthRange.first, params.mainRoadLengthRange.second);
        printf("Main road length: %d\n", mainRoadLength);
        glm::vec2i endPos = startpos;
        endPos.y += mainRoadLength - 1;
        assert(!roadmap.isPositionOutside(endPos));


        //for initial line:
        roadmap.setLine(startpos, CompassDirection::NORTH, mainRoadLength, true);

        auto genBranch = [&roadmap, &params](bool direction, const glm::vec2i& pos) -> int{

            int linelength = Random::get()->randInt(params.branchRoadLengthRange.first, params.branchRoadLengthRange.second); // branch length
            auto startPos = pos;
            startPos.x += direction ? 1 : -1;
            roadmap.setLine(startPos, direction ? CompassDirection::EAST : CompassDirection::WEST, linelength, 1);
            return linelength;

        };

        int maxLBranchLength = 0, maxRBranchLength = 0;
        //for branches:
        for (glm::vec2i pos = startpos; pos.y <= endPos.y ;)
        {
            int junctionChoice = Random::get()->randInt(0,2);
            /*
                0: left
                1: right
                2: both left and right
            */
            if (junctionChoice == 0 || junctionChoice == 2) {// left
                int branchLength = genBranch(0, pos);
                maxLBranchLength = std::max(branchLength, maxLBranchLength);
            }

            if(junctionChoice == 1 || junctionChoice == 2) {// right
                int branchLength = genBranch(1, pos);
                maxRBranchLength = std::max(branchLength, maxRBranchLength);
            }

            //end steps:
            pos.y += Random::get()->randInt(params.branchStepRange.first, params.branchStepRange.second);
        }

        TreeGenData returnData;
        returnData.dims = {maxLBranchLength + 1 + maxRBranchLength, mainRoadLength};
        returnData.maxLBranchLength = maxLBranchLength;
        returnData.maxRBranchLength = maxRBranchLength;
        return returnData;

    }

    std::pair<glm::vec2i, glm::vec2i> treePosToBufferAndGlobal(
            bool orientation,
            const glm::vec2i& placePos,
            const glm::vec2i& treePos,
            int treeWidth,
            int bufferMaxBranchLength,
            int maxLBranchLength)
    {
        glm::vec2i bufferPos = treePos;
        bufferPos.x += bufferMaxBranchLength - maxLBranchLength;

        glm::vec2i globalPos;
        if(orientation == 1) // horizontal
        {
            globalPos = {treePos.y, -treePos.x + treeWidth - 1};
            globalPos += placePos;
        } else {//vertical
            globalPos = treePos + placePos;
        }

        return {bufferPos, globalPos};
    }


    TreeGenerator::TreeGenerator(const TreeGenParams &params)
        :treeData(std::make_unique<RoadMap>(1 + 2 * params.branchRoadLengthRange.second, params.mainRoadLengthRange.second)), params(params),
          lastGenData(std::make_unique<TreeGenData>())
    {}


    glm::vec2i TreeGenerator::generate()
    {
        *lastGenData = generateTree(*treeData, {params.branchRoadLengthRange.second, 0}, params);
        std::cout << "Finished generating\n";
        return lastGenData->dims;
    }



    void TreeGenerator::writeTo(RoadMap& roadMap, glm::vec2i startPos, bool orientation)
    {
        //write#


        //go through every logical tree position
        const glm::vec2i& dims = lastGenData->dims;
        glm::vec2i treePos{0,0};
        for (; treePos.x < dims.x; treePos.x++)
        {
            for(treePos.y = 0; treePos.y < dims.y; treePos.y++)
            {
                //find out different coordinates
                auto tmp = treePosToBufferAndGlobal(orientation, startPos, treePos, dims.x, params.branchRoadLengthRange.second, lastGenData->maxLBranchLength);
                glm::vec2i& bufferPos = tmp.first;
                glm::vec2i& globalPos = tmp.second;

                roadMap.setFieldState(globalPos, treeData->getFieldState(bufferPos));
            }
        }
        treeData->clear();

    }

    TreeGenerator::~TreeGenerator() = default;

}
