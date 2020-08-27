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

void RoadMapGen::generate()
{
    Generator::TreeGenParams params;

    params.mainRoadLengthRange = {10,15};
    params.branchRoadLengthRange = {10, 14};
    params.branchStepRange = {2, 3};
    Generator::TreeGenerator treeGen(params);

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


    auto closestPointInfo = rpr.getClosestPoint();


    //new code
    /*
    bool orientation = 0;

    const int N_ITERATIONS = 10;
    RANGE_FOR(i, 0, N_ITERATIONS)
    {
        //generate and get dimensions
        glm::vec2i dims = treeGen.generate();
        //get closest point
        auto closestPointInfo = rpr.getClosestPoint();


        //find out if there is space
        bool canBeHorizontal =

        treeGen.writeTo(*roadMap, placePos, orientation);
        rpr.placeRectangle(placePos, dims);



    }
    */
}

RoadMapGen::~RoadMapGen()
{

}
