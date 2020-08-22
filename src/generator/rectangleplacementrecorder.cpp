#include <algorithm>

#include "rectangleplacementrecorder.h"
#include "../util/CompassDirection.h"
#include "lineFunc.h"
#include "../util/printVar.h"

template<typename T>
struct Square
{
    glm::vec2i pos;
    glm::vec2i dims;
};

namespace Generator {

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
            std::list<Line> newLines; // the lines for the new square
            getLinesForSquare(lines, square);

            //find lines already in the envelope, which contact with lines in square. If there are none, complain
            //for every of those lines, 'subtract' the portion which meets the line of the square

        }
    }

    ClosestPointInfo RectanglePlacementRecorder::getClosestPoint()
    {
#define LINE_DISTANCE(l) glm::length(static_cast<glm::vec2>(getClosestPointOnLineToOtherPoint(l, origin)))
        auto closestLineIt = std::min_element(lines.begin(), lines.end(),[this](const Line& l1, const Line& l2) -> bool {

            return LINE_DISTANCE(l1) < LINE_DISTANCE(l2);
        } );


        auto closestPoint = getClosestPointOnLineToOtherPoint(*closestLineIt, origin);
        return{closestPoint};

    }


}
