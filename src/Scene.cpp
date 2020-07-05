#include "Scene.h"

#include "Input.h"

void generateTree(RoadMap& roadmap, const glm::vec2i& startpos);

Scene::Scene()
    :roadMap(width, height), roadGenerator(&roadMap)
{
    generateTree(roadMap, glm::vec2i(25, 5));
}

void Scene::update()
{
    //roadGenerator.performOneIteration();
    if (Input::getKeyEvent(GLFW_KEY_K) == GLFW_PRESS)
        this->roadMap.toggleFieldState(glm::vec2i(1,1));
}
