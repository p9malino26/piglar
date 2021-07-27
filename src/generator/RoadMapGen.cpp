#include "RoadMapGen.h"

#include <optional>

#include "TreeGenParams.h"
#include "TreeGenerator.h"

#include "../TileMap.h"
#include "../tileMapUtil.h"

#include "BottomUpRectPlacer.h"

#include "../util/Random.h"
#include "../util/compassUtil.h"

//prototypes


namespace Generator {
    std::vector<std::pair<BoardPos, Rectangle>> generateRoadsAndHouses(TileMap& tileMap, const TreeGenParams& params)
    {
        BottomUpRectPlacer rpr(tileMap.getWidth(), tileMap.getHeight());
        TreeGenerator treeGen(params);

        NeighbouringInfo& surroundingNeighbours = rpr.getNeighbouringSpaceInfo();
        for (;;)
        {
            //generate
            BoardPos dims = treeGen.generate();
            ++dims.x;
            ++dims.y;

            //think of orientation
            bool orientation = Random::get()->fiftyFifty();
            if (orientation) // horizontal
                dims = glm::swap(dims);

            //see if it fits
            std::optional<BoardPos> optPlacePos = rpr.placeRectangle(reinterpret_cast<Rectangle&>(dims));

            //if yes
            if (optPlacePos.has_value())
            {
                //write tree to roadmap
                auto& placePos = optPlacePos.value();
                treeGen.writeTo(tileMap, placePos, orientation);

                auto connectToOther = [&tileMap, &placePos] (CompassDirection direction, int limit)
                {
                    auto startPos = placePos;
                    if (limit == 0) return;
                    int offset = limit >> 1;

                    if (direction != CompassDirection::SOUTH)
                        startPos.y += offset;

                    if (direction == CompassDirection::WEST || direction == CompassDirection::SOUTH)
                        startPos.x += offset;


                    fillLineUntilTouchingRoad(tileMap, startPos, direction);
                    fillLineUntilTouchingRoad(tileMap, startPos, opposite(direction));

                };

                connectToOther(CompassDirection::EAST, surroundingNeighbours.east);
                connectToOther(CompassDirection::SOUTH, surroundingNeighbours.south);
                connectToOther(CompassDirection::WEST, surroundingNeighbours.west);


            } else
                break;
        }

        return rpr.getEmptySpaces();
    }

    template <typename RectList>
    void generateGreenAreas(TileMap& tileMap, const RectList& greenAreaRects) {
        for (const std::pair<BoardPos, Rectangle>& info: greenAreaRects)
        {
            forEachInRegion(tileMap, info.first, info.second, [] (TileState& tileState) {if (tileState != HORIZONTAL && tileState != VERTICAL) tileState = GREEN_SPACE;});

        }
    }

    void generateTerrain(TileMap& tileMap, const TreeGenParams& params)
    {
        std::vector<std::pair<BoardPos, Rectangle>> greenSpaceInfo = generateRoadsAndHouses(tileMap, params);
        generateGreenAreas(tileMap, greenSpaceInfo);
    }

}
