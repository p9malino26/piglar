#pragma once

#include <list>
#include "../../util/Rectangle.h"
#include "../../util/line.h"
#include "../../util/vectors.h"
#include <optional>


typedef std::list<Line>::iterator LinePtr;

class RectLinesInfo;

class MinimumAreaInfo;

struct NeighbouringInfo {int east, south, west;};

class BottomUpRectPlacer
{
public:
    BottomUpRectPlacer(int width, int height);
    std::optional<BoardPos> placeRectangle(const Rectangle& rect);
    inline NeighbouringInfo& getNeighbouringSpaceInfo() { return neighbouringSpaceInfo;}
    //debug
    void consistencyCheck();

    std::vector<std::pair<BoardPos, Rectangle>> getEmptySpaces();
private:
    int width, height;
    std::list<Line> envelope;
    std::vector<std::pair<BoardPos, Rectangle>> emptySpaces;
    NeighbouringInfo neighbouringSpaceInfo;

    BoardPos placeRectangleFinal(MinimumAreaInfo& contactingLines, RectLinesInfo& rectLines);
    void mergeLines(LinePtr existing, Line& newLine);
    void checkForSplitLines(LinePtr line);
    std::optional<LinePtr> checkForSplitLines(LinePtr left, LinePtr right);
    MinimumAreaInfo getMinimumAreaLines();
    std::pair<BoardPos, Rectangle> seclude(MinimumAreaInfo& minimumAreaInfo);


};
