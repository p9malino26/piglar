//
// Created by patryk on 28/06/2021.
//

#pragma once

#include "TileMap.h"

class Rectangle;
typedef std::function<void(TileState&)> TileFunc;

bool isOnRoad(const TileMap& tileMap, const RealPos& pos);
inline BoardPos realToTile(const RealPos& pos);
BoardPos clampToNearestTile(const RealPos& pos);
BoardPos getClosestPosWithRoad(const TileMap& tileMap, const BoardPos& pos);
void fillLineUntilTouchingRoad(TileMap &roadMap, const BoardPos& start, CompassDirection direction);
void setLine(TileMap& tileMap, const glm::vec2i& startPos, CompassDirection direction, int length);
void forEachOnLine(TileMap& tileMap, const glm::vec2i& startPos, CompassDirection direction, int length, std::function<void(TileState&)> tileFunc);
void forEachInRegion(TileMap& tileMap, const BoardPos& rectPos, const Rectangle& rectDims, TileFunc tileFunc);
inline TileState compassToRoadOrientation(CompassDirection compassDirection) { return TileState(1 + ((int)compassDirection + 1) % 2); }
inline int pos2Index(int width, const BoardPos& pos) { return width * pos.y + pos.x; }
