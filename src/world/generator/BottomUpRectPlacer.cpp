#include <algorithm>
#include <utility>

#include "BottomUpRectPlacer.h"
#include "rectUtil.h"
#include "../../util/lineUtil.h"

#include "../../util/lineConsistencyCheck.h"


struct MinimumAreaInfo
{
    LinePtr minimumLine;
    std::optional<LinePtr> leftOfMinimum, rightOfMinimum;
};

BottomUpRectPlacer::BottomUpRectPlacer(int width, int height) : width(width),
    height(height)
{
    envelope.push_back(Line({0,0}, width, CompassDirection::EAST));
}


//RectLinesInfo getRectLines(const Rectangle& rect);

inline int getLineHeight(std::optional<LinePtr> maybeLinePtr) {
    int height = 0;
    if (maybeLinePtr.has_value()) {
        height = maybeLinePtr.value()->length;
    }
    return height;
}

std::optional<BoardPos> BottomUpRectPlacer::placeRectangle(const Rectangle &rect)
{
    RectLinesInfo rectLines = getRectLines(rect);

    for (;;)
    {
        MinimumAreaInfo contactingLines = getMinimumAreaLines();

        auto& minimumLine = *contactingLines.minimumLine;

        if(minimumLine.pos.y + rect.height > this->height) return {};

        if (minimumLine.length < rectLines.bottom.length)
        {
            emptySpaces.push_back(seclude(contactingLines));
            continue;
        }


        neighbouringSpaceInfo.south = minimumLine.pos.y == 0 ? 0 : rect.width;
        neighbouringSpaceInfo.east = std::min(rect.height, getLineHeight(contactingLines.leftOfMinimum));
        neighbouringSpaceInfo.west = std::min(rect.height, getLineHeight(contactingLines.rightOfMinimum));

        return placeRectangleFinal(contactingLines, rectLines);
    }

}



void BottomUpRectPlacer::consistencyCheck()
{
    lineConsistencyCheck(envelope.begin(), envelope.end());
}


BoardPos BottomUpRectPlacer::placeRectangleFinal(MinimumAreaInfo& contactingLines, RectLinesInfo& rectLines)
{
    auto lineTransform = [&contactingLines](Line& l) {
        //l.pos.x *= rectLines.bottom.length;
        //l.pos.y *= rectLines.left.length;
        l.pos += contactingLines.minimumLine->pos;

    };


    std::for_each(&rectLines.left, &rectLines.bottom+1, lineTransform);
    //lineConsistencyCheck(&rectLines.left, &rectLines.bottom + 1);
    LinePtr newTop = envelope.insert(contactingLines.minimumLine, rectLines.top);

    if (contactingLines.leftOfMinimum.has_value()) {
        mergeLines(contactingLines.leftOfMinimum.value(), rectLines.left);
    }

    auto& minimumLine = contactingLines.minimumLine;
    auto insertPos = contactingLines.minimumLine->pos;
    auto minLineLength = minimumLine->length;
    mergeLines(contactingLines.minimumLine, rectLines.bottom);
    auto& newBottom = minimumLine;

    if (rectLines.bottom.length == minLineLength) {
        if (contactingLines.rightOfMinimum.has_value())
            mergeLines(contactingLines.rightOfMinimum.value(), rectLines.right);
    } else
        envelope.insert(newBottom, rectLines.right);

    checkForSplitLines(newTop);
    return insertPos;

}

void BottomUpRectPlacer::mergeLines(LinePtr existing, Line& newLine)
{
    auto difference = lineDifference(*existing, newLine);
    if (!difference.has_value()) {
        envelope.erase(existing);
    } else {
        *existing = difference.value();
    }
}

void BottomUpRectPlacer::checkForSplitLines(LinePtr line)
{
    LinePtr left(line), right(line);
    left--;
    right++;

    std::optional<LinePtr> maybeNewLine;

    if (left != envelope.end())
        maybeNewLine = checkForSplitLines(left, line);

    if (right != envelope.end())
    {
        if (maybeNewLine.has_value()) line = maybeNewLine.value();
        checkForSplitLines(line, right);
    }


}

std::optional<LinePtr> BottomUpRectPlacer::checkForSplitLines(LinePtr left, LinePtr right)
{
    std::optional<Line> newLine = joinLines(*left, *right);
    if (newLine.has_value())
    {
        envelope.erase(right);
        *left = newLine.value();
        return left;
    }
    return {};
}

MinimumAreaInfo BottomUpRectPlacer::getMinimumAreaLines()
{
    MinimumAreaInfo output;
    int minHeight = height;
    LinePtr minimumLine;

    for(auto linePtr = envelope.begin(); linePtr != envelope.end(); linePtr++)
    {
        if (linePtr->direction == CompassDirection::EAST && linePtr->pos.y < minHeight)
        {
            minimumLine = linePtr;
            minHeight = linePtr->pos.y; //bug
        }

    }

    LinePtr leftOf = minimumLine, rightOf = minimumLine;
    leftOf--;
    rightOf++;

    auto checkValid = [this](LinePtr lp) -> std::optional<LinePtr> {return lp == envelope.end() ? std::optional<LinePtr>() : std::optional<LinePtr>(lp);};

    return {minimumLine, checkValid(leftOf), checkValid(rightOf) };

}

//seclude
std::pair<BoardPos, Rectangle> BottomUpRectPlacer::seclude(MinimumAreaInfo& contactingLines)
{
    std::pair<BoardPos, Rectangle> spaceInfo;
    auto& minimumLine = contactingLines.minimumLine;
    spaceInfo.first = minimumLine->pos;
    int yVal = height;

    auto updateLineHeight = [this, &yVal](std::optional<LinePtr>& maybeLine) {
        if (maybeLine.has_value())
        {
            auto& line = maybeLine.value();
            yVal = std::min(yVal, line->direction == CompassDirection::SOUTH ? line->pos.y : tip(*line).y);
            envelope.erase(line);
        }
    };


    updateLineHeight(contactingLines.leftOfMinimum);
    updateLineHeight(contactingLines.rightOfMinimum);
    spaceInfo.second.width =  minimumLine->length;
    spaceInfo.second.height = yVal - minimumLine->pos.y;

    minimumLine->pos.y = yVal;

    auto leftHorizonal = minimumLine, rightHorizontal = minimumLine;
    leftHorizonal--;
    rightHorizontal++;

    if (leftHorizonal != envelope.end())
    {
        if (!checkForSplitLines(leftHorizonal, minimumLine).has_value())
        {
            envelope.insert(minimumLine, lineBetween(tip(*leftHorizonal), minimumLine->pos));
        } else {
            minimumLine = rightHorizontal;
            minimumLine--;
        }
    }

    if (rightHorizontal != envelope.end())
    {
        if (!checkForSplitLines(minimumLine, rightHorizontal).has_value())
        {
            envelope.insert(rightHorizontal, lineBetween(tip(*minimumLine), rightHorizontal->pos));
        }

    }

    return spaceInfo;
}

    std::vector<std::pair<BoardPos, Rectangle>> BottomUpRectPlacer::getEmptySpaces() {
        return emptySpaces;
    }
