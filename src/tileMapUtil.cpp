//
// Created by patryk on 28/06/2021.
//

#include "tileMapUtil.h"

#include "util/compassUtil.h"
#include "util/Rectangle.h"

bool isOnRoad(const TileMap& tileMap, const RealPos& pos)
{
    BoardPos intpos = realToTile(pos);
    if (tileMap.isPositionOutside(intpos)) return false;
    auto state = tileMap.getTileState(intpos);
    return isRoad(state);
}

BoardPos realToTile(const RealPos& pos)
{
    return {std::floor(pos.x), std::floor(pos.y)};//wasbug
}

BoardPos clampToNearestTile(const RealPos& pos)
{
    return realToTile(pos + RealPos{0.5f, 0.5f});
}

BoardPos getClosestPosWithRoad(const TileMap& tileMap, const BoardPos& pos)
{
    if (isRoad(tileMap.getTileState(pos))) return pos;

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
                if (isRoad(tileMap.getTileState(d))) return d;
                d += directions[i];
            }
        }
    }
    return getClosestPosWithRoad(tileMap, pos - BoardPos(1,1));
}

bool contactsRoads(const TileMap& roadMap, const BoardPos& pos, CompassDirection direction) {
    auto getFieldStateNoThrow = [&roadMap] (const BoardPos& pos) {
        if (roadMap.isPositionOutside(pos)) return false;

        return (bool) roadMap.getTileState(pos);
    };

    return getFieldStateNoThrow(pos + directionVec(compassDirFromRelative(direction, RelativeDirection::LEFT))) ||
           getFieldStateNoThrow(pos + directionVec(compassDirFromRelative(direction, RelativeDirection::RIGHT))) ||
           getFieldStateNoThrow(pos + directionVec(direction));

}

void setLine(TileMap& tileMap, const BoardPos& startPos, CompassDirection direction, int length)
{
    TileState state = compassToRoadOrientation(direction);
    forEachOnLine(tileMap, startPos, direction, length, [&state](TileState& tile) {tile = state; });
}

void fillLineUntilTouchingRoad(TileMap &roadMap, const BoardPos& start, CompassDirection direction) {
    auto pos = start;
    TileState roadState = compassToRoadOrientation(direction);
    for(;;) {
        if (roadMap.isPositionOutside(pos)) break;
        roadMap.setTileState(pos, roadState);
        pos += directionVec(direction);
        if (contactsRoads(roadMap, pos, direction))
        {
            roadMap.setTileState(pos, roadState);
            break;
        }
    }
}

void forEachOnLine(TileMap& tileMap, const BoardPos& startPos, CompassDirection direction, int length, std::function<void(TileState&)> tileFunc)
{
    BoardPos theDirectionVec = directionVec(direction);
    BoardPos varPos = startPos;
    for (int i = 0; i < length; i++, varPos+=theDirectionVec)
    {
        tileFunc(tileMap.getTile(varPos));
    }
}

void forEachInRegion(TileMap& tileMap, const BoardPos& rectPos, const Rectangle& rect, TileFunc tileFunc)
{
    int farY = rectPos.y + rect.height;
    for(auto varPos = rectPos; varPos.y < farY; ++varPos.y)
    {
        TileState* start = &tileMap.getTile(varPos);
        std::for_each(start, start + rect.width, tileFunc);
    }
}