#include "lineFunc.h"
#include <algorithm>

glm::vec2i getClosestPointOnLineToOtherPoint(const Line& line, const glm::vec2i& point)
{
    int linePos_varComponent;
    int pos_compComponent;
    bool sign;

    auto& x = line.pos.x;
    auto& y = line.pos.y;

    switch (line.direction)
    {
    case CompassDirection::NORTH:
        linePos_varComponent = y;
        pos_compComponent = point.y;
        sign = 1;
        break;
    case CompassDirection::EAST:
        linePos_varComponent = x;
        pos_compComponent = point.x;
        sign = 1;
        break;
    case CompassDirection::SOUTH:
        linePos_varComponent = y;
        pos_compComponent = point.y;
        sign = 0;
        break;

    case CompassDirection::WEST:
        linePos_varComponent = x;
        pos_compComponent = point.y;
        sign = 0;
        break;
    }

    int closest;
    if (sign == 1){
        /*if north:
         *
        */
        closest = std::clamp(pos_compComponent, linePos_varComponent, linePos_varComponent + line.length);
    } else
    {
        closest = std::clamp(pos_compComponent, linePos_varComponent - line.length, linePos_varComponent);
    }

    if (line.direction == CompassDirection::NORTH || line.direction == CompassDirection::SOUTH)
        return {x, closest};
    else
        return {closest, y};
}
