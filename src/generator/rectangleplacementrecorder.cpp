#include <algorithm>

#include "rectangleplacementrecorder.h"
#include "../util/CompassDirection.h"
#include "lineFunc.h"
#include "../util/printVar.h"
#include "../util/rangeFor.h"

template<typename T>
struct Square
{
    glm::vec2i pos;
    glm::vec2i dims;
};


namespace Generator {

    struct LineTouchInfo
    {
        enum {GOOD_CONTACT, NO_CONTACT, BAD_CONTACT} contact;
        int newLineCount;
        int lines[2];
    };

    //for every of those lines, 'subtract' the portion which meets the line of the square
    LineTouchInfo getLineTouchInfo(const Line& ll1, const Line& ll2);

    RectanglePlacementRecorder::RectanglePlacementRecorder(const glm::vec2i& origin)
        :origin(origin)
    {
        PRINTVAR(origin);
    }

    RectanglePlacementRecorder::~RectanglePlacementRecorder() = default;

    namespace  {
    void getLinesForSquare(std::list<Line>& lineList, const Square<int>& square){
        auto varPos = square.pos;
        auto& dims = square.dims;
        //left
        lineList.emplace_back(varPos, dims.y, CompassDirection::NORTH);
        //top
        varPos.y += dims.y;
        lineList.emplace_back(varPos, dims.x, CompassDirection::EAST);
        //right
        varPos.x += dims.x;
        lineList.emplace_back(varPos, dims.y, CompassDirection::SOUTH);
        //bottom
        varPos.y -= dims.y;
        lineList.emplace_back(varPos, dims.x, CompassDirection::WEST);
    }
    }




    void Generator::RectanglePlacementRecorder::placeRectangle(const glm::vec2i &pos, const glm::vec2i &dims)
    {
        Square<int> square{pos, dims};
        if (lines.size() == 0)
        {
            getLinesForSquare(lines, square);

        } else
        {
            // get list of lines for the new square
            std::list<Line> squareLines;
            getLinesForSquare(squareLines, square);

            //find lines already in the envelope, which contact with lines in square.
            for (auto squareLineIt = squareLines.begin(); squareLineIt != squareLines.end(); squareLineIt++)
            {
                //TODO exception handling??
                for (auto mainLineIt = lines.begin(); mainLineIt != lines.end(); mainLineIt++)
                {
                    //check how the two lines interact
                    auto lineTouchInfo = getLineTouchInfo(*squareLineIt, *mainLineIt);
                    //when they touch correctly
                    if (lineTouchInfo.contact == LineTouchInfo::GOOD_CONTACT)
                    {
                        //make copy of main lines iterator
                        auto newLinesInsertPos = mainLineIt;
                        newLinesInsertPos++;
                        //remove contacting lines from both square lines and main lines
                        squareLines.erase(squareLineIt);
                        lines.erase(mainLineIt);
                        //insert the new lines resulting form the contact
                        lines.insert(newLinesInsertPos, lineTouchInfo.lines, lineTouchInfo.lines + lineTouchInfo.newLineCount);
                        //and the remaining lines for the square

                    }
                }
            }

            //


        }
    }

    ClosestPointInfo RectanglePlacementRecorder::getClosestPoint()
    {
#define LINE_DISTANCE(l) glm::length(static_cast<glm::vec2>(getClosestPointOnLineToOtherPoint(l, origin)))
        auto closestLineIt = std::min_element(mainLines.begin(), mainLines.end(),[this](const Line& l1, const Line& l2) -> bool {

            return LINE_DISTANCE(l1) < LINE_DISTANCE(l2);
        } );


        auto closestPoint = getClosestPointOnLineToOtherPoint(*closestLineIt, origin);
        return{closestPoint};

    }


}
