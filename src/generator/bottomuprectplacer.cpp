#include <algorithm>
#include <utility>

#include "bottomuprectplacer.h"
#include "rectUtil.h"
#include "../util/lineFunc.h"

#include "../util/lineConsistencyCheck.h"

namespace Generator {

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

BottomUpRectPlacer::BottomUpRectPlacer()
    :width(100), height(100)
{
    envelope = {
        Line({0,10}, 10, CompassDirection::EAST),
        Line({10,10}, 10, CompassDirection::SOUTH),
        Line({10,0}, 10, CompassDirection::EAST),
        Line({20,0}, 20, CompassDirection::NORTH),
        Line({20,20}, 80, CompassDirection::EAST)
    };

    MinimumAreaInfo contactInfo = getMinimumAreaLines();
    seclude(contactInfo);
    consistencyCheck();
}

//RectLinesInfo getRectLines(const Rectangle& rect);

std::optional<Pos> BottomUpRectPlacer::placeRectangle(const Rectangle &rect)
{
    RectLinesInfo rectLines = getRectLines(rect);

    while (true) {
        MinimumAreaInfo contactingLines = getMinimumAreaLines();

        auto& minimumLine = *contactingLines.minimumLine;

        if(minimumLine.pos.y + rect.height > this->height) return {};

        if (minimumLine.length < rectLines.bottom.length)
        {
            seclude(contactingLines);
            continue;
        }

        return placeRectangleFinal(contactingLines, rectLines);
    }

}



void BottomUpRectPlacer::consistencyCheck()
{
    lineConsistencyCheck(envelope.begin(), envelope.end());
}


//todo remove const
Pos BottomUpRectPlacer::placeRectangleFinal( MinimumAreaInfo& contactingLines,  RectLinesInfo& rectLines)
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
void BottomUpRectPlacer::seclude(MinimumAreaInfo& contactingLines)
{
    auto& minimumLine = contactingLines.minimumLine;
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


    //old stuff
    /*int touchingLinesInfo = checkForSplitLines(minimumAreaInfo.minimumLine);
    if (~touchinfLinesInfo & 2)
        auto beforeLeft = minimumAreaInfo
    //--
    LinePtr touchingLine;
    if (minimumAreaInfo.leftOfMinimum.has_value())
    {
        LinePtr& leftOfMinimum = minimumAreaInfo.leftOfMinimum.value();
        if (minimumAreaInfo.rightOfMinimum.has_value())
            touchingLine = leftOfMinimum->pos.y <= tip(*minimumAreaInfo.rightOfMinimum.value()->pos.y) ? leftOfMinimum : minimumAreaInfo.rightOfMinimum;
        else
            touchingLine = leftOfMinimum;
    } else if (minimumAreaInfo.rightOfMinimum.has_value())
        touchingLine = minimumAreaInfo.rightOfMinimum.value();

    if (touchingLine == minimumAreaInfo.leftOfMinimum.value_or(envelope.end()))
        //todo finish
    envelope.erase(touchingLine);
    checkForSplitLines(minimumAreaInfo.minimumLine);*/
}



}
