#pragma once

#include "../util/line.h"
#include "../GLMIncludes.h"

glm::vec2i getClosestPointOnLineToOtherPoint(const Line& line, const glm::vec2i& point);
