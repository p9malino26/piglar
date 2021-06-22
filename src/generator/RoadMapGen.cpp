#include "RoadMapGen.h"

#include <algorithm>
#include <optional>

#include "../GLMIncludes.h"

#include "../RoadMap.h"

#include "../generator/TreeGenerator.h"
#include "../generator/bottomuprectplacer.h"

#include "../util/rangeFor.h"
#include "../util/Random.h"
#include "../util/compassUtil.h"

//prototypes

bool contactsRoads(const RoadMap& roadMap, const Pos& pos, CompassDirection direction) {
    auto getFieldStateNoThrow = [&roadMap] (const Pos& pos) {
        if (roadMap.isPositionOutside(pos)) return false;

        return roadMap.getFieldState(pos);
    };

    return getFieldStateNoThrow(pos + directionVec(compassDirFromRelative(direction, RelativeDirection::LEFT))) ||
           getFieldStateNoThrow(pos + directionVec(compassDirFromRelative(direction, RelativeDirection::RIGHT))) ||
           getFieldStateNoThrow(pos + directionVec(direction));

}

namespace Generator {

    void fillLineUntilTouchingRoad(RoadMap& roadMap, const Pos& start, CompassDirection direction);




    RoadMapGen::RoadMapGen(RoadMap* roadMap)
        :roadMap(roadMap), rpr(new BottomUpRectPlacer(roadMap->getWidth(), roadMap->getHeight()))
    {
    }

    void RoadMapGen::generate()
    {

        TreeGenParams params;

        params.mainRoadLengthRange = {10,15};
        params.branchRoadLengthRange = {10, 14};
        params.branchStepRange = {2, 4};
        TreeGenerator treeGen(params);



        //prototype 2509


        auto& surroundingNeighbours = rpr->getNeighbouringSpaceInfo();
        while (1)
        {
            //generate
            glm::vec2i dims = treeGen.generate();
            ++dims.x;
            ++dims.y;

            //think of orientation
            bool orientation = Random::get()->fiftyFifty();
            if (orientation) // horizontal
                dims = glm::swap(dims);

            //see if it fits
            std::optional<glm::vec2i> optPlacePos = rpr->placeRectangle(reinterpret_cast<Rectangle&>(dims));

            //if yes
            if (optPlacePos.has_value())
            {
                //write tree to roadmap
                auto& placePos = optPlacePos.value();
                treeGen.writeTo(*roadMap, placePos, orientation);

                auto connectToOther = [this] (CompassDirection direction, int limit, const Pos &startPos)
                {
                    if (limit == 0) return;
                    int offset = limit >> 1;

                    CompassDirection posDirection = ((int)direction % 2) == 1 ? CompassDirection::NORTH : CompassDirection::EAST;

                    Pos start = startPos + directionVec(posDirection) * offset;
                    fillLineUntilTouchingRoad(*roadMap, start, direction);
                    fillLineUntilTouchingRoad(*roadMap, start - directionVec(direction), opposite(direction));

                };

                connectToOther(CompassDirection::EAST, surroundingNeighbours.east, placePos);
                connectToOther(CompassDirection::SOUTH, surroundingNeighbours.south, placePos);
                connectToOther(CompassDirection::WEST, surroundingNeighbours.west, placePos + Pos(dims.x, 0));


            } else
                break;


        }
    }



    RoadMapGen::~RoadMapGen()
    {
    }

    void fillLineUntilTouchingRoad(RoadMap &roadMap, const Pos &start, CompassDirection direction) {
        auto pos = start;
        decltype(pos) oldPos;
        do {
            roadMap.setFieldState(pos, true);
            oldPos = pos;
            pos += directionVec(direction);
        } while (!contactsRoads(roadMap, oldPos, direction) && !roadMap.isPositionOutside(pos));
    }

}
