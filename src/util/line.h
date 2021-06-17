#pragma once

#include "../GLMIncludes.h"
#include "CompassDirection.h"

struct Line{
    glm::vec2i pos;
    int length;
    CompassDirection direction;

    Line(){}
    Line(const glm::vec2i &pos, int length, CompassDirection direction) : pos(pos), length(length),
                                                                         direction(direction) {}
};
