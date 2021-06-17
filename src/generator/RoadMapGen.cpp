#include "RoadMapGen.h"

#include <algorithm>
#include <optional>

#include "../GLMIncludes.h"

#include "../RoadMap.h"

#include "../generator/TreeGenerator.h"
#include "../generator/bottomuprectplacer.h"

#include "../util/rangeFor.h"
#include "../util/printVar.h"
#include "../util/Random.h"

//prototypes

namespace Generator {


    RoadMapGen::RoadMapGen(RoadMap* roadMap)
        :roadMap(roadMap), rpr(new BottomUpRectPlacer(roadMap->getWidth(), roadMap->getHeight()))
    {
    }

    void RoadMapGen::generate()
    {

        TreeGenParams params;

        params.mainRoadLengthRange = {10,15};
        params.branchRoadLengthRange = {10, 14};
        params.branchStepRange = {2, 4};
        TreeGenerator treeGen(params);



        //prototype 2509


        while (1)
        {
            //generate
            glm::vec2i dims = treeGen.generate();
            ++dims.x;
            ++dims.y;

            //think of orientation
            bool orientation = Random::fiftyFifty();
            if (orientation) // horizontal
                dims = glm::swap(dims);

            //see if it fits
            std::optional<glm::vec2i> optPlacePos = rpr->placeRectangle(reinterpret_cast<Rectangle&>(dims));

            //if yes
            if (optPlacePos.has_value())
            {
                //write tree to roadmap
                treeGen.writeTo(*roadMap, optPlacePos.value(), orientation);
            } else
                break;

            //ClosestPointInfo cpi = rpr->getClosestPoint();

        }
    }



    RoadMapGen::~RoadMapGen()
    {

    }

}
