//TODO get rid of this file and split it into multiple
#ifndef UTIL_H
#define UTIL_H

#include "GLMIncludes.h"


extern const glm::vec2i NORTH_VEC;
extern const glm::vec2i EAST_VEC ;
extern const glm::vec2i SOUTH_VEC;
extern const glm::vec2i WEST_VEC ;


enum class CompassDirection {NORTH, EAST, SOUTH, WEST};
enum class RelativeDirection {RIGHT, LEFT};

CompassDirection compassDirFromRelative(CompassDirection compDir, RelativeDirection relDir);

const glm::vec2i& directionVec(CompassDirection);

inline constexpr int clockwiseDirectionAngle(CompassDirection d) {
    switch (d)
    {
        case CompassDirection::NORTH:
            return 0;
        case CompassDirection::EAST:
            return 90;
        case CompassDirection::SOUTH:
            return 180;
        case CompassDirection::WEST:
            return 270;
    }
}


struct Fraction
{
    Fraction(int num, int den)
        :numerator(num), denominator(den)
    {}
    
    int numerator, denominator;
};



//const glm::vec2& getRandomDirection


#endif
