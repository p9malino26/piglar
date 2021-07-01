//
// Created by patryk on 28/06/2021.
//

#pragma once

#include "TileMap.h"

bool isOnRoad(const TileMap& tileMap, const RealPos& pos);
inline BoardPos realToTile(const RealPos& pos);
BoardPos clampToNearestTile(const RealPos& pos);