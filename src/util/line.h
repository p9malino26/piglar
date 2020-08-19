#pragma once

#include "../GLMIncludes.h"
#include "compassUtil.h"

struct Line{
    glm::vec2i pos;

    int length;
    CompassDirection direction;

    Line(const glm::vec2i &pos, int length, CompassDirection direction) : pos(pos), length(length),
                                                                          direction(direction) {}
};
