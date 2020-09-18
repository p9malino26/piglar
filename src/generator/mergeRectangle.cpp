#include <tuple>
#include <optional>
#include <algorithm>

#include "mergeRectangle.h"

#include "findFirstContact.h"
#include "../util/Rectangle.h"

namespace Generator {

    void getLinesForRectangle(std::list<Line>& lineList, const Rectangle& square){
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

    typedef std::list<Line>::const_iterator ConstLineItr;
    typedef std::list<Line>::iterator LineItr;

    /** finds first line from envelope going clockwise that contacts with the square
    */

    std::tuple<LineItr, LineItr, LineTouchInfo> getFirstContactPoint(std::list<Line>& envelopeLines, std::list<Line>& squareLines)
    {
        struct EnvelopeContactInfo {LineTouchInfo lineTouchInfo; LineItr squareLine;};
        //this lambda checks if an envelope line contacts with a square line and returns the relevant info if yes
        auto checkEnvelopeContact = [&squareLines] (const Line& envelopeLine) -> std::optional<EnvelopeContactInfo> {};

        //LineItr envelopeItr;
        //std::optional<EnvelopeContactInfo> possibleEnvelopeContactInfo;
        //auto& contactInfo = possibleEnvelopeContactInfo.value();
        EnvelopeContactInfo* envelopeContactInfo;

        //is there contact at the front?
        auto optFrontContact = checkEnvelopeContact(*envelopeLines.begin());
        //yes
        if (optFrontContact.has_value())
        {
            auto& frontContact = optFrontContact.value();

            //if there is a contact at the end, keep going back the chain of contacts until you find a contactless line
            auto goingBackContactInfo = checkEnvelopeContact(*envelopeLines.end());
            auto& backContactInfo = goingBackContactInfo;

            if(backContactInfo.has_value())
            {
                auto& _goingBackContactInfo = goingBackContactInfo.value();
                auto envelopeItr = envelopeLines.end();
                do
                {
                    envelopeItr--;
                } while (checkEnvelopeContact(*envelopeItr).has_value());

                //start off at penultimate
                while (true)
                {
                    //check the one before
                    envelopeItr--;
                    auto backOneContactInfo = checkEnvelopeContact(*envelopeItr);
                    if (backOneContactInfo.has_value())
                    {
                        goingBackContactInfo = backOneContactInfo;
                    //keep doing this until you find one where there is no contact before
                    } else {
                        envelopeItr++;
                        return {envelopeItr, _goingBackContactInfo.squareLine, _goingBackContactInfo.lineTouchInfo};
                    }
                }

            //yes contact at the front,no contact at the end:
            } else {

                return std::make_tuple(envelopeLines.begin(), frontContact.squareLine, frontContact.lineTouchInfo);
            }
        }
        //no contact at the front
        else {
            auto envelopeItr = envelopeLines.begin();
            envelopeItr++;
            while (true)
            {
                if(checkEnvelopeContact(*envelopeItr).has_value())
                {
                    return envelopeItr;
                }
                envelopeItr++;
            }
        }
    }

    std::optional<LineTouchInfo> findContact(const Line& line, const std::list<Line>& envelopeLines);
    void mergeIfNecessary(const Line& line, const std::list<Line>& envelopeLines);

    inline void mergeLines(const std::list<Line>& envelopeLines, const std::list<Line>& squareLines);
    void transposeLinesToEnvelope(std::list<Line>& lines, const glm::vec2& origin);

    /**
     * Finds closest point to origin outside group of rectangles, attempts to place rectangle there
     */
    void mergeRectangle(std::list<Line>& envelopeLines, const Rectangle& rectangle)
    {
        if (envelopeLines.size() == 0)
        {
            getLinesForRectangle(envelopeLines, rectangle);

        }
        else
        {
            // get list of envelopeLines for the new square
            std::list<Line> squareLines;
            getLinesForRectangle(squareLines, rectangle);


            auto [envelepePtr, squarePtr, contactInfo] = getFirstContactPoint(envelopeLines, squareLines);
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
                    envelopeLines.erase(envelepePtr);
                    //TODO move the pointer to the back
                    envelopeLines.insert(envelepePtr, contactInfo.resultingLines, contactInfo.resultingLines + contactInfo.newLineCount);
                } else {
                    envelopeLines.insert(envelepePtr, *squarePtr);
                    mergeIfNecessary(*squarePtr, envelopeLines);
                }

                envelepePtr++;
                if (squarePtr == squareLines.end())
                {
                    squarePtr++;
                }
            }
        }
    }

    void mergeLines(std::list<Line>& envelopeLines, std::list<Line>& squareLines)
    {
        envelopeLines.merge(squareLines, [] (const Line& l1, const Line& l2) {return true;});
    }

    void transposeLinesToEnvelope(std::list<Line>& lines, const glm::vec2& origin)
    {
        std::for_each(lines.begin(), lines.end(), [&origin] (Line& l) {l.pos += origin;});
    }
}
