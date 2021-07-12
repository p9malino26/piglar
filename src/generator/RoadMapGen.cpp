#include "RoadMapGen.h"

#include <optional>

#include "TreeGenParams.h"
#include "TreeGenerator.h"

#include "../TileMap.h"

#include "bottomuprectplacer.h"

#include "../util/Random.h"
#include "../util/compassUtil.h"

//prototypes

bool contactsRoads(const TileMap& roadMap, const Pos& pos, CompassDirection direction) {
    auto getFieldStateNoThrow = [&roadMap] (const Pos& pos) {
        if (roadMap.isPositionOutside(pos)) return false;

        return roadMap.getFieldState(pos);
    };

    return getFieldStateNoThrow(pos + directionVec(compassDirFromRelative(direction, RelativeDirection::LEFT))) ||
           getFieldStateNoThrow(pos + directionVec(compassDirFromRelative(direction, RelativeDirection::RIGHT))) ||
           getFieldStateNoThrow(pos + directionVec(direction));

}

namespace Generator {

    void fillLineUntilTouchingRoad(TileMap& roadMap, const Pos& start, CompassDirection direction);


    RoadMapGen::RoadMapGen(TileMap* roadMap, const TreeGenParams& params)
        :roadMap(roadMap), rpr(new BottomUpRectPlacer(roadMap->getWidth(), roadMap->getHeight())), treeGen(new TreeGenerator(params))
    {
    }

    void RoadMapGen::generate()
    {

        auto& treeGen = *this->treeGen;

        NeighbouringInfo& surroundingNeighbours = rpr->getNeighbouringSpaceInfo();
        for (;;)
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

                auto connectToOther = [this, &placePos] (CompassDirection direction, int limit)
                {
                    auto startPos = placePos;
                    if (limit == 0) return;
                    int offset = limit >> 1;

                    if (direction != CompassDirection::SOUTH)
                        startPos.y += offset;

                    if (direction == CompassDirection::WEST || direction == CompassDirection::SOUTH)
                        startPos.x += offset;


                    fillLineUntilTouchingRoad(*roadMap, startPos, direction);
                    fillLineUntilTouchingRoad(*roadMap, startPos, opposite(direction));

                };

                connectToOther(CompassDirection::EAST, surroundingNeighbours.east);
                connectToOther(CompassDirection::SOUTH, surroundingNeighbours.south);
                connectToOther(CompassDirection::WEST, surroundingNeighbours.west);


            } else
            break;
        }
    }



    RoadMapGen::~RoadMapGen()
    {
    }

    void fillLineUntilTouchingRoad(TileMap &roadMap, const Pos &start, CompassDirection direction) {
        auto pos = start;
        for(;;) {
            if (roadMap.isPositionOutside(pos)) break;
            roadMap.setFieldState(pos, true);
            pos += directionVec(direction);
            if (contactsRoads(roadMap, pos, direction))
            {
                roadMap.setFieldState(pos, true);
                break;
            }
        }
    }

}
