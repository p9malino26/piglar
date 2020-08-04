#include "Scene.h"

#include "RoadMap.h"
#include "Input.h"
#include "generator/generator.h"

#include "util/printVar.h"

void generateRoadMap(RoadMap* roadMap);

Scene::Scene()
    :roadMap(new RoadMap(width, height))
{
    generateRoadMap(roadMap.get());
}

void Scene::update()
{
    //roadGenerator.performOneIteration();
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
    glm::vec2 dims = treeGen.generate();
    PRINTVAR(dims);
    treeGen.writeTo(*roadMap,{10,10}, 0);

}
