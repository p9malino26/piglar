#include "rectangleplacementrecorder.h"

#include <tuple>
#include <optional>

#include "findFirstContact.h"

struct Square
{
    glm::vec2i pos;
    glm::vec2i dims;
};

namespace Generator {

    void getLinesForSquare(std::list<Line>& lineList, const Square& square){
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

    struct LineTouchInfo
    {
        int newLineCount;
        int resultingLines[2];
    };

    std::optional<LineTouchInfo> getLineTouchInfo(const Line& ll1, const Line& ll2);

    typedef std::list<Line>::iterator LinePtr;

    void transposeLinesToEnvelope(std::list<Line>& lines, const glm::vec2& origin);

    /** finds first line from envelope going clockwise that contacts with the square
    */
    std::tuple<LinePtr, LinePtr, LineTouchInfo> getFirstContactPoint(const std::list<Line>& envelopeLines, const std::list<Line>& squareLines)
    {
        auto checkSquareLines = [&squareLines] (LinePtr envelopeIterator) -> std::optional<LineTouchInfo> {
            for (auto squareIterator = squareLines.begin(); squareIterator != squareLines.end(); squareIterator++)
            {
                auto possibleTouchInfo = getLineTouchInfo(*envelopeIterator, *squareIterator);
                if (possibleTouchInfo.has_value())
                {
                    return possibleTouchInfo;
                }
            }
            return std::optional<LineTouchInfo>();
        };



        LineTouchInfo getFirstPointOfContact(envelopeLines.begin(), envelopeLines.end(), checkSquareLines);
    }

    std::optional<LineTouchInfo> findContact(const Line& line, const std::list<Line>& envelopeLines);
    void mergeIfNecessary(const Line& line, const std::list<Line>& envelopeLines);

    void RectanglePlacementRecorder::placeRectangle(const glm::vec2i &pos, const glm::vec2i &dims)
    {
        Square square{pos, dims};
        if (lines.size() == 0)
        {
            getLinesForSquare(lines, square);

        } else
        {
            // get list of lines for the new square
            std::list<Line> squareLines;
            getLinesForSquare(squareLines, square);
            transposeLinesToEnvelope(squareLines, origin);

            /*LinePtr envelepePtr, squarePtr;
            LineTouchInfo contactInfo;*/
            auto [envelepePtr, squarePtr, contactInfo] = getFirstContactPoint(lines, squareLines);
            bool contactProcessed = true;

            int squareLineCount = 4;
            //for every line in the square
            for (; squareLineCount > 0; squareLineCount--, squarePtr++)
            {
                //see if square line contacts anything
                bool contactFound = true;
                if(!contactProcessed)
                {
                    //find a contact !!
                    auto possibleContactInfo = findContact();
                    if (possibleContactInfo.has_value())
                    {
                        contactInfo = possibleContactInfo.value();
                        contactFound = true;
                    }
                    else
                        contactFound = false;

                    contactProcessed = false;
                }

                if (contactFound)
                {
                    lines.erase(envelepePtr);
                    //TODO move the pointer to the back
                    lines.insert(envelepePtr, contactInfo.resultingLines, contactInfo.resultingLines + contactInfo.newLineCount);
                } else {
                    lines.insert(envelepePtr, *squarePtr);
                    mergeIfNecessary(*squarePtr, lines);
                }

                envelepePtr++;
                if (squarePtr == squareLines.end())
                {
                    squarePtr++;
                }
            }
        }
    }
}
