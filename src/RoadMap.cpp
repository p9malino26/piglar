#include "RoadMap.h"


RoadMap::RoadMap(int width, int height)
    :width(width), height(height), data(width * height)
{
   
}

void RoadMap::setLine(const glm::vec2i& startPos, CompassDirection direction, int length, bool state)
{
    glm::vec2i theDirectionVec = directionVec(direction);
    //glm::vec2i endPos = startPos+ length *
    glm::vec2i varPos = startPos;
    for (int i = 0; i < length; i++, varPos+=theDirectionVec)
    {
        setFieldState(varPos, state);
    }
}
