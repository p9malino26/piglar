#pragma once

#include "CompassDirection.h"
#include "vectors.h"

const glm::vec2i& directionVec(CompassDirection);

extern const glm::vec2i NORTH_VEC;
extern const glm::vec2i EAST_VEC ;
extern const glm::vec2i SOUTH_VEC;
extern const glm::vec2i WEST_VEC ;

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
glm::vec2i rotatePoint(const glm::vec2i& pos, int direction);

inline constexpr CompassDirection rotateAcw(CompassDirection dir, int factor) // todo rename
{
    return CompassDirection( ( (int)dir - factor + 4) % 4);
}
