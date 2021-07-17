#pragma once

#include "CompassDirection.h"
#include "compassVec.h"

enum class RelativeDirection {RIGHT, LEFT};
CompassDirection compassDirFromRelative(CompassDirection compDir, RelativeDirection relDir);

inline constexpr int clockwiseDirectionAngle(CompassDirection d) {
    switch (d)
    {
        case CompassDirection::NORTH:
            return 0;
        case CompassDirection::EAST:
            return 90;
        case CompassDirection::SOUTH:
            return 180;
        default:
            return 270;
    }
}

inline constexpr int directionNumber(CompassDirection dir) {return (int)dir; }
inline constexpr CompassDirection opposite (CompassDirection direction) {return CompassDirection((int(direction) + 2) % 4);}
