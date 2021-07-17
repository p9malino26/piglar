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
inline CellType compassToRoadOrientation(CompassDirection compassDirection) { return CellType(1 + ((int)compassDirection + 1) % 2); }
