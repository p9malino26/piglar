#include "RoadMap.h"
#include "Scene.h"

#include "Input.h"
#include "generator/generator.h"
#include "generator/rectangleplacementrecorder.h"

#include "util/rangeFor.h"

void generateRoadMap(RoadMap* roadMap);

Scene::Scene()
    :roadMap(new RoadMap(width, height))
{
    generateRoadMap(roadMap.get());
}

void Scene::update()
{
    //roadGenerator.performOcneIteration();
    if (Input::getKeyEvent(GLFW_KEY_K) == GLFW_PRESS)
        this->roadMap->toggleFieldState(glm::vec2i(1,1));
}

Scene::~Scene() = default;

void generateRoadMap(RoadMap* roadMap)
{
    Generator::TreeGenParams params;

    params.mainRoadLengthRange = {10,15};
    params.branchRoadLengthRange = {4, 6};
    params.branchStepRange = {2, 3};
    Generator::TreeGenerator treeGen(params);

    auto getStartPos = [](const glm::vec2i& roadMapsize, const glm::vec2i& dims) -> glm::vec2i {
        glm::vec2i offset = dims / 2;
        return roadMapsize / 2 - offset;
    };


    Generator::RectanglePlacementRecorder rpr;

    //generate and write
    auto dims = treeGen.generate();
    auto placePos = getStartPos({roadMap->getWidth(), roadMap->getHeight()}, dims);
    treeGen.writeTo(*roadMap, placePos, 0);

    //record
    rpr.placeRectangle(placePos, dims);

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
