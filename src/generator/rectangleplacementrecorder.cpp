#include "rectangleplacementrecorder.h"
#include "../Util.h"

namespace Generator {

    RectanglePlacementRecorder::RectanglePlacementRecorder() {}
    RectanglePlacementRecorder::~RectanglePlacementRecorder() = default;


    void Generator::RectanglePlacementRecorder::placeRectangle(const glm::vec2i &pos, const glm::vec2i &dims)
    {
        if (lines.size() == 0)
        {
            auto varPos = pos;
            //left
            lines.emplace_back(varPos, dims.y, CompassDirection::NORTH);
            //top
            varPos.y += dims.y;
            lines.emplace_back(varPos, dims.x, CompassDirection::EAST);
            //right
            varPos.x += dims.x;
            lines.emplace_back(varPos, dims.y, CompassDirection::SOUTH);
            //bottom
            varPos.y -= dims.y;
            lines.emplace_back(varPos, dims.x, CompassDirection::WEST);
        } else
        {

        }
    }

}
