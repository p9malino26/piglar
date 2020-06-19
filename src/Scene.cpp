#include "Scene.h"

#include "Input.h"

Scene::Scene()
    :roadMap(width, height), roadGenerator(&roadMap)
{
    //roadGenerator.generate();
}

void Scene::update()
{
    //roadGenerator.performOneIteration();
    if (Input::getKeyEvent(GLFW_KEY_K) == GLFW_PRESS)
        this->roadMap.toggleFieldState(glm::vec2i(1,1));
}
