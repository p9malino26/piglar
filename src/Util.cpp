#include "GLMIncludes.h"

#include "Util.h"

const glm::vec2i NORTH_VEC =   glm::vec2i(0, 1);
const glm::vec2i EAST_VEC  =   glm::vec2i(1, 0);
const glm::vec2i SOUTH_VEC =  -NORTH_VEC;
const glm::vec2i WEST_VEC  =  -EAST_VEC;


const glm::vec2i & directionVec ( CompassDirection direction)
{

    switch(direction)
    {
        case CompassDirection::NORTH:
            return NORTH_VEC;
        case CompassDirection::EAST:
            return EAST_VEC;
        case CompassDirection::SOUTH:
            return SOUTH_VEC;
        case CompassDirection::WEST:
            return WEST_VEC;
    }
}

CompassDirection compassDirFromRelative ( CompassDirection compDir, RelativeDirection relDir )
{
    switch (compDir)
    {
        case CompassDirection::NORTH:
            if (relDir == RelativeDirection::RIGHT) return CompassDirection::EAST;
            else return CompassDirection::WEST;
        case CompassDirection::EAST:
            if (relDir == RelativeDirection::RIGHT) return CompassDirection::SOUTH;
            else return CompassDirection::NORTH;            
        case CompassDirection::SOUTH:
            if (relDir == RelativeDirection::RIGHT) return CompassDirection::WEST;
            else return CompassDirection::EAST;            
        case CompassDirection::WEST:
            if (relDir == RelativeDirection::RIGHT) return CompassDirection::NORTH;
            else return CompassDirection::SOUTH;            
    }
}