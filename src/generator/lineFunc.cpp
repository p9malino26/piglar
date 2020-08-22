#include "lineFunc.h"
#include <algorithm>

glm::vec2i getClosestPointToPoint(const Line& line)
{
    int varComponent; // x= -4
    bool sign; // +

    auto& x = line.pos.x;
    auto& y = line.pos.y;

    switch (line.direction)
    {
    case CompassDirection::NORTH:
        varComponent = y;
        sign = 1;
        break;
    case CompassDirection::EAST:
        varComponent = x;
        sign = 1;
        break;
    case CompassDirection::SOUTH:
        varComponent = y;
        sign = 0;
        break;

    case CompassDirection::WEST:
        varComponent = x;
        sign = 0;
        break;
    }

    int closest;
    if (sign == 1){
        closest = std::clamp(0, varComponent, varComponent + line.length);
    } else
    {
        closest = std::clamp(0, varComponent - line.length, varComponent);
    }

    if (line.direction == CompassDirection::NORTH || line.direction == CompassDirection::SOUTH)
        return {x, closest};
    else
        return {closest, y};
}
