#include "Scene.h"

#include "RoadMap.h"
#include "Input.h"
#include "generator/generator.h"

#include "util/printVar.h"

Scene::Scene()
    :roadMap(new RoadMap(width, height))
{
    Generator::TreeGenParams params;

    params.mainRoadLengthRange = {10,15};
    params.branchRoadLengthRange = {4, 6};
    params.branchStepRange = {2, 3};
    Generator::TreeGenerator treeGen(params);
    treeGen.generateAndWrite({10,10}, *roadMap, 1);
    //auto rectSize = Generator::generateTree(roadMap, glm::vec2i(25, 5), params);
    //PRINTVAR(rectSize);
}

void Scene::update()
{
    //roadGenerator.performOneIteration();
    if (Input::getKeyEvent(GLFW_KEY_K) == GLFW_PRESS)
        this->roadMap->toggleFieldState(glm::vec2i(1,1));
}

Scene::~Scene() = default;
