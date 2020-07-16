#include "Scene.h"

#include "Input.h"
#include "generator/generator.h"

#include "util/printVar.h"

Scene::Scene()
    :roadMap(width, height), roadGenerator(&roadMap)
{
    Generator::TreeGenParams params;
    params.mainRoadLengthRange = {10,15};
    params.branchRoadLengthRange = {4, 6};
    params.branchStepRange = {2, 3};
    treeGen = std::make_unique<Generator::TreeGenerator>(params);
    //Generator::TreeGenerator treeGen(params);
    treeGen->generate();
    //auto rectSize = Generator::generateTree(roadMap, glm::vec2i(25, 5), params);
    //PRINTVAR(rectSize);
}

void Scene::update()
{
    //roadGenerator.performOneIteration();
    if (Input::getKeyEvent(GLFW_KEY_K) == GLFW_PRESS)
        this->roadMap.toggleFieldState(glm::vec2i(1,1));
}
