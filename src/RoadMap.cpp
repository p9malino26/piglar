#include "RoadMap.h"

#include "util/compassVec.h"

RoadMap::RoadMap(int width, int height)
    :width(width), height(height), data(new CellType[width * height])
{
    clear();
}

void RoadMap::setLine(const glm::vec2i& startPos, CompassDirection direction, int length, CellType state)
{
    glm::vec2i theDirectionVec = directionVec(direction);
    //glm::vec2i endPos = startPos+ length *
    glm::vec2i varPos = startPos;
    for (int i = 0; i < length; i++, varPos+=theDirectionVec)
    {
        setFieldState(varPos, state);
    }
}
