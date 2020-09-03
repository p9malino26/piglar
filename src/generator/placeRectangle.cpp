#include "rectangleplacementrecorder.h"

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

            LineTouchInfo lineTouchInfo;
            std::list<Line>::iterator mainLineIt;
            std::list<Line>::iterator squareLineIt;
            bool contactFound = true;

            getInitialPointOfContact(mainLineIt, squareLineIt, lineTouchInfo);


            //find lines already in the envelope, which contact with lines in square.
            int squareLineCount = 4;
            for (; squareLineCount > 0; squareLineCount--)
            {
                for (auto _mainLineIt = lines.begin(); mainLineIt != lines.end(); mainLineIt++)
                {
                    if(! contactFound)
                        lineTouchInfo = getLineTouchInfo(*squareLineIt, *_mainLineIt);

                    if (lineTouchInfo.contact == LineTouchInfo::GOOD_CONTACT) {
                        // remove main line and square
                    }

                } else {
                    //add line to envelope
                    lines.insert(squareLineIt, *squareLineIt);
                }

            }
            {
                {
                    //check how the two lines interact
                    auto lineTouchInfo = getLineTouchInfo(*squareLineIt, *mainLineIt);
                    //when they touch correctly
                        envelopeFirstContactPoint = lineTouchInfo;
                        envelopePlaceIt = mainLineIt;
                    }
                }
            }
                    //--
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
}
