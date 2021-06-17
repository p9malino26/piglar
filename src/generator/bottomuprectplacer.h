#pragma once

#include <list>
#include "../GLMIncludes.h"
#include "Rectangle.h"
#include "../util/line.h"
#include <optional>


typedef glm::vec2i Pos;
typedef std::list<Line>::iterator LinePtr;

class RectLinesInfo;
namespace Generator {

class MinimumAreaInfo;


class BottomUpRectPlacer
{
public:
    BottomUpRectPlacer(int width, int height);
    BottomUpRectPlacer();
    std::optional<Pos> placeRectangle(const Rectangle& rect);
    //debug
    void consistencyCheck();
private:
    int width, height;
    std::list<Line> envelope;

    Pos placeRectangleFinal( MinimumAreaInfo& contactingLines, RectLinesInfo& rectLines);
    void mergeLines(LinePtr existing, Line& newLine);
    void checkForSplitLines(LinePtr line);
    std::optional<LinePtr> checkForSplitLines(LinePtr left, LinePtr right);
    MinimumAreaInfo getMinimumAreaLines();
    void seclude(MinimumAreaInfo& minimumAreaInfo);


};
}
