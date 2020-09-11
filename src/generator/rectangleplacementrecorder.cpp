#include "rectangleplacementrecorder.h"

#include <algorithm>
#include "../util/CompassDirection.h"
#include "lineFunc.h"
#include "../util/printVar.h"
#include "../util/rangeFor.h"



namespace Generator {

    //for every of those lines, 'subtract' the portion which meets the line of the square

    RectanglePlacementRecorder::RectanglePlacementRecorder(const glm::vec2i& origin)
        :origin(origin)
    {
        PRINTVAR(origin);
    }

    RectanglePlacementRecorder::~RectanglePlacementRecorder() = default;


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
