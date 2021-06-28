//
// Created by patryk on 28/06/2021.
//

#pragma once

#include "RoadMap.h"

bool isOnRoad(const RoadMap& tileMap, const RealPos& pos);
inline BoardPos realToTile(const RealPos& pos);
BoardPos clampToNearestTile(const RealPos& pos);