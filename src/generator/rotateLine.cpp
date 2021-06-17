#include "../util/line.h"
#include "../util/getRotateAcwMatrix.h"
#include "../util/rotateCompassDir.h"
#include "../util/getRotateAcwMatrix.h"

glm::vec2i rotatePoint(const glm::vec2i& pos, int direction)
{
    direction = (direction + 4) % 4;
    switch (direction)
    {
    case 1:
        return {-pos.y, pos.x};
    case 2:
        return {-pos.x, -pos.y};
    case 3:
        return {pos.y, -pos.x};
    default:
        return pos;
    }
}

//TODO move!
Line rotateLine(const Line& line, int direction)
{
    return Line(rotatePoint(line.pos, direction), line.length, rotateAcw(line.direction, direction));
}
