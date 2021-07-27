#include <optional>
#include "line.h"
#include "compassUtil.h"

glm::vec2i tip(const Line& l)
{
    return l.pos + directionVec(l.direction) * l.length;
}

//TODO move!
Line rotateLine(const Line& line, int direction)
{
    return Line(rotatePoint(line.pos, direction), line.length, rotateAcw(line.direction, direction));
}


std::optional<Line> lineDifference(const Line& main, const Line& other)
{
    Line l {{}, std::abs(main.length - other.length), {}};
    if (l.length == 0) return {};

    int rotateDir = directionNumber(main.direction);
    auto main_rot = rotateLine(main, rotateDir);
    auto other_rot = rotateLine(other, rotateDir);

    if (other_rot.direction != CompassDirection::SOUTH) return {};

    if (tip(main_rot) == other_rot.pos){
        l.pos = main_rot.pos;
        if (tip(other_rot).y > main_rot.pos.y)
            l.direction = CompassDirection::NORTH;
        else
            l.direction = CompassDirection::SOUTH;
    } else if (main_rot.pos == tip(other_rot)) {
        l.pos = other_rot.pos;
        if (tip(main_rot).y > other_rot.pos.y)
            l.direction = CompassDirection::NORTH;
        else
            l.direction = CompassDirection::SOUTH;
    } else assert(false);

    return rotateLine(l, -rotateDir);
}


std::optional<Line> joinLines(Line & l1, Line &l2)
{
    if(tip(l1) == l2.pos && l1.direction == l2.direction)
        return {Line(l1.pos, l1.length + l2.length, l1.direction)};

    return {};
}

//linebetween

Line lineBetween(const glm::vec2i& p1, const glm::vec2i& p2)
{
    Line toReturn;
    toReturn.pos = p1;
    assert (p1.x == p2.x);

    toReturn.direction = p1.y < p2.y ? CompassDirection::NORTH : CompassDirection::SOUTH;//wasug
    toReturn.length = std::abs(p1.y - p2.y);

    return toReturn;
}
