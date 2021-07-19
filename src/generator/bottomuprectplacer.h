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

struct NeighbouringInfo {int east, south, west;};

class BottomUpRectPlacer
{
public:
    BottomUpRectPlacer(int width, int height);
    std::optional<Pos> placeRectangle(const Rectangle& rect);
    inline NeighbouringInfo& getNeighbouringSpaceInfo() { return neighbouringSpaceInfo;}
    //debug
    void consistencyCheck();

    std::vector<std::pair<Pos, Rectangle>> getEmptySpaces();
private:
    int width, height;
    std::list<Line> envelope;
    std::vector<std::pair<Pos, Rectangle>> emptySpaces;
    NeighbouringInfo neighbouringSpaceInfo;

    Pos placeRectangleFinal( MinimumAreaInfo& contactingLines, RectLinesInfo& rectLines);
    void mergeLines(LinePtr existing, Line& newLine);
    void checkForSplitLines(LinePtr line);
    std::optional<LinePtr> checkForSplitLines(LinePtr left, LinePtr right);
    MinimumAreaInfo getMinimumAreaLines();
    std::pair<Pos, Rectangle> seclude(MinimumAreaInfo& minimumAreaInfo);


};
}
