#include "RoadMap.h"
#include "Scene.h"
#include "Input.h"

void generateRoadMap(RoadMap* roadMap);

Scene::Scene()
    :roadMap(new RoadMap(width, height))
{
}

void Scene::update()
{
    //roadGenerator.performOcneIteration();
    if (Input::getKeyEvent(GLFW_KEY_K) == GLFW_PRESS)
        this->roadMap->toggleFieldState(glm::vec2i(1,1));
}

Scene::~Scene() {
}
