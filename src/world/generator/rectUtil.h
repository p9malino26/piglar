#pragma once

#include "../../util/Rectangle.h"
#include "../../util/line.h"


struct RectLinesInfo
{
    Line left, top, right, bottom;
};

RectLinesInfo getRectLines(const Rectangle& rect);
