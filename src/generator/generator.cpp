#include <iostream>
#include "../RoadMap.h"
#include "../GLMIncludes.h"
#include "../Random.h"
#include "Params.h"

#define CONSTANT(EXPR) \
static constexpr EXPR;

namespace Generator
{

    void generateTree(RoadMap& roadmap, const glm::vec2i& startpos, const Params& params)
    {
        assert(!roadmap.isPositionOutside(startpos));

        int mainRoadLength = Random::randInt(params.mainRoadLengthRange.first, params.mainRoadLengthRange.second);
        glm::vec2i endPos = startpos + glm::vec2i(0, mainRoadLength);
        assert(!roadmap.isPositionOutside(endPos));


        //for initial line:
        for (glm::vec2i pos = startpos; ; pos.y++)
        {
            roadmap.setFieldState(pos, true);
            if (pos.y == endPos.y)
                break;
        }

        auto genBranch = [&roadmap, &params](bool direction, const glm::vec2i& pos) {

            int linelength = Random::randInt(params.branchRoadLengthRange.first, params.branchRoadLengthRange.second); // branch length
            roadmap.setLine(pos, direction ? CompassDirection::WEST : CompassDirection::EAST, linelength, 1);

        };

        //for branches:
        for (glm::vec2i pos = startpos; pos.y <= endPos.y ;)
        {
            int junctionChoice = Random::randInt(0,2);
            /*
                0: left
                1: right
                2: both left and right
            */

            if (junctionChoice == 0 || junctionChoice == 2) // left
                genBranch(0, pos);

            if(junctionChoice == 1 || junctionChoice == 2) // right
                genBranch(1, pos);

            //end steps:
            pos.y += Random::randInt(params.branchStepRange.first, params.branchStepRange.second);
        }

    }

}
