//
// Created by patryk on 28/06/2021.
//

#pragma once

#include "TileMap.h"

bool isOnRoad(const TileMap& tileMap, const RealPos& pos);
inline BoardPos realToTile(const RealPos& pos);
BoardPos clampToNearestTile(const RealPos& pos);
BoardPos getClosestPosWithRoad(const TileMap& tileMap, const BoardPos& pos);
void fillLineUntilTouchingRoad(TileMap &roadMap, const BoardPos& start, CompassDirection direction);
void setLine(TileMap& tileMap, const glm::vec2i& startPos, CompassDirection direction, int length);
void forEachOnLine(TileMap& tileMap, const glm::vec2i& startPos, CompassDirection direction, int length, std::function<void(TileState&)> tileFunc);
inline TileState compassToRoadOrientation(CompassDirection compassDirection) { return TileState(1 + ((int)compassDirection + 1) % 2); }
