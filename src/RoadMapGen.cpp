#include "RoadMapGen.h"

#include <algorithm>
#include "GLMIncludes.h"

#include "RoadMap.h"

#include "generator/TreeGenerator.h"
#include "generator/rectangleplacementrecorder.h"

#include "util/rangeFor.h"
#include "util/printVar.h"

RoadMapGen::RoadMapGen(RoadMap* roadMap)
    :roadMap(roadMap)
{
    rpr = std::make_unique<Generator::RectanglePlacementRecorder>(roadMap->getSize() / 2);

}

glm::vec2i toFinalPlacePos(const Generator::ClosestPointInfo& closestPointInfo, const glm::vec2i& dims);

void RoadMapGen::generate()
{
    using namespace Generator;
    TreeGenParams params;

    params.mainRoadLengthRange = {10,15};
    params.branchRoadLengthRange = {10, 14};
    params.branchStepRange = {2, 3};
    TreeGenerator treeGen(params);

    auto getStartPos = [](const glm::vec2i& roadMapsize, const glm::vec2i& dims) -> glm::vec2i {
        glm::vec2i offset = dims / 2;
        return roadMapsize / 2 - offset;
    };


    //generate and write
    auto dims = treeGen.generate();
    auto placePos = getStartPos({roadMap->getWidth(), roadMap->getHeight()}, dims);
    treeGen.writeTo(*roadMap, placePos, 0);

    //record
    rpr->placeRectangle(placePos, dims);

    /*
    //get closest point
    auto closestPointInfo = rpr->getClosestPoint();

    //generate again
    dims = treeGen.generate();
    rpr->placeRectangle(toFinalPlacePos(closestPointInfo, dims), dims);*/
}

glm::vec2i toFinalPlacePos(const Generator::ClosestPointInfo& closestPointInfo, const glm::vec2i& dims)
{
}

RoadMapGen::~RoadMapGen()
{

}
