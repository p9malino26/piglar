#include "rectUtil.h"

RectLinesInfo getRectLines(const Rectangle& rect) {
    RectLinesInfo toReturn;
    glm::vec2i varPos{0,0};
    //left
    toReturn.left = {varPos, rect.height, CompassDirection::NORTH};
    //top
    varPos.y += rect.height;
    toReturn.top = {varPos, rect.width, CompassDirection::EAST};
    //right
    varPos.x += rect.width;
    toReturn.right = {varPos, rect.height, CompassDirection::SOUTH};
    //bottom
    varPos.y -= rect.height;
    toReturn.bottom = {varPos, rect.width, CompassDirection::WEST};
    return toReturn;
}
