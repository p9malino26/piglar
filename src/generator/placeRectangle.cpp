#include "rectangleplacementrecorder.h"

#include <tuple>

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
        enum {GOOD_CONTACT, NO_CONTACT, BAD_CONTACT} contact;
        int newLineCount;
        int lines[2];
    };

    //for every of those lines, 'subtract' the portion which meets the line of the square
    LineTouchInfo getLineTouchInfo(const Line& ll1, const Line& ll2);

    typedef std::list<Line>::iterator LinePtr;

    void transposeLinesToEnvelope(std::list<Line>& lines, const glm::vec2& origin);
    std::tuple<LinePtr, LinePtr, LineTouchInfo> getFirstContactPoint(const std::list<Line>& envelopeLines, const std::list<Line>& squareLines);
    LineTouchInfo findContact(const Line& line, const std::list<Line>& envelopeLines);
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
            bool contactFound = true;

            int squareLineCount = 4;
            for (; squareLineCount > 0; squareLineCount--, squarePtr++)
            {
                //see if square line contacts anything
                if(! contactFound)
                {
                    //find a contact !!
                    contactInfo = findContact(*squarePtr, lines);
                    contactFound = false;
                }

                if (contactInfo.contact == LineTouchInfo::GOOD_CONTACT)
                {
                    lines.erase(envelepePtr);
                    //TODO move the pointer to the back
                    lines.insert(envelepePtr, contactInfo.lines, contactInfo.lines + contactInfo.newLineCount);
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
