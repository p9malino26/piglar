#pragma once
#include <optional>

#include "line.h"
#include "compassUtil.h"

std::optional<Line> lineDifference(const Line& l1, const Line& l2);

Line rotateLine(const Line& line, int direction);


std::optional<Line> joinLines(Line&, Line&);
Line lineBetween(const glm::vec2i& p1, const glm::vec2i& p2);

glm::vec2i tip(const Line& l);
