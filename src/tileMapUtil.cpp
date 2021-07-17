//
// Created by patryk on 28/06/2021.
//

#include "tileMapUtil.h"

#include "util/compassUtil.h"


bool isOnRoad(const TileMap& tileMap, const RealPos& pos)
{
    BoardPos intpos = realToTile(pos);
    if (tileMap.isPositionOutside(intpos)) return false;
    return tileMap.getFieldState(intpos);
}

inline BoardPos realToTile(const RealPos& pos)
{
    return {std::floor(pos.x), std::floor(pos.y)};//wasbug
}

BoardPos clampToNearestTile(const RealPos& pos)
{
    return realToTile(pos + RealPos{0.5f, 0.5f});
}

BoardPos getClosestPosWithRoad(const TileMap& tileMap, const BoardPos& pos)
{
    if (tileMap.getFieldState(pos)) return pos;

    const BoardPos* directions = &NORTH_VEC;
    BoardPos checkDirections[] = {NORTH_VEC, EAST_VEC, SOUTH_VEC, WEST_VEC};

    std::for_each(checkDirections, checkDirections + 4, [&pos](auto& p) {p += pos;});

    bool canGoFurther = true;
    while (canGoFurther)
    {
        canGoFurther = false;
        for (int i = 0; i < 4; i++)
        {
            auto& d = checkDirections[i];
            if (!tileMap.isPositionOutside(d))
            {
                canGoFurther = true;
                if (tileMap.getFieldState(d)) return d;
                d += directions[i];
            }
        }
    }

}

bool contactsRoads(const TileMap& roadMap, const BoardPos& pos, CompassDirection direction) {
    auto getFieldStateNoThrow = [&roadMap] (const BoardPos& pos) {
        if (roadMap.isPositionOutside(pos)) return false;

        return (bool)roadMap.getFieldState(pos);
    };

    return getFieldStateNoThrow(pos + directionVec(compassDirFromRelative(direction, RelativeDirection::LEFT))) ||
           getFieldStateNoThrow(pos + directionVec(compassDirFromRelative(direction, RelativeDirection::RIGHT))) ||
           getFieldStateNoThrow(pos + directionVec(direction));

}

void fillLineUntilTouchingRoad(TileMap &roadMap, const BoardPos& start, CompassDirection direction) {
    auto pos = start;
    CellType roadState = compassToRoadOrientation(direction);
    for(;;) {
        if (roadMap.isPositionOutside(pos)) break;
        roadMap.setFieldState(pos, roadState);
        pos += directionVec(direction);
        if (contactsRoads(roadMap, pos, direction))
        {
            roadMap.setFieldState(pos, roadState);
            break;
        }
    }
}
