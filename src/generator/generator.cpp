#include <iostream>
#include <random>

#include "../RoadMap.h"
#include "../GLMIncludes.h"
#include "../Random.h"

#define CONSTANT(EXPR) \
static constexpr EXPR;

void generateTree(RoadMap& roadmap, const glm::vec2i& startpos)
{
    assert(!roadmap.isPositionOutside(startpos));
    CONSTANT(int MIN_MAINROAD_LENGTH = 4)
    CONSTANT(int MAX_MAINROAD_LENGTH = 15)

    int mainRoadLength = Random::randInt(MIN_MAINROAD_LENGTH, MAX_MAINROAD_LENGTH);
    glm::vec2i endPos = startpos + glm::vec2i(0, mainRoadLength);
    assert(!roadmap.isPositionOutside(endPos));


    //for initial line:
    for (glm::vec2i pos = startpos; ; pos.y++)
    {
        roadmap.setFieldState(pos, true);
        if (pos.y == endPos.y)
            break;
    }

    auto genBranch = [](bool direction, const glm::vec2i& pos) {
        bool x = Random::fractionChance({2,3}); // choose whether to generate branch
        if (x)
        {
            int linelength = Random::randInt(3, 7);
            roadmap.fillLine(pos, direction, linelength );
        }

    }

    //for branches:
    for (glm::vec2i pos = startpos; ;pos.y <= startpos.y)
    {

        genBranch(0, startpos);
        genBranch(1, startpos);

        //end steps:
        pos.y += Random::randInt(1, 3);
    }

}