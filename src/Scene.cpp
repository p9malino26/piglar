#include "RoadMap.h"
#include "Scene.h"
#include "Input.h"

#include "generator/RoadMapGen.h"
#include "MouseManager.h"


void generateRoadMap(RoadMap* roadMap);

namespace Generator {
    void fillLineUntilTouchingRoad(RoadMap &roadMap, const glm::vec2i &start, CompassDirection direction);
}

Scene::Scene()
    :roadMap(new RoadMap(width, height)), roadMapGen(new Generator::RoadMapGen(roadMap.get()))
{
    roadMapGen->generate();
}

void Scene::update()
{
    //roadGenerator.performOcneIteration();
    if (Input::mouseHasClicked()) {
        glm::vec2 mouseWorldPos = MouseManager::get()->getWorldMousePos();
        glm::vec2i intMouseWorldPos = glm::vec2i((int)mouseWorldPos.x, (int)mouseWorldPos.y);
        std::cout << "Mouse position: " << intMouseWorldPos << std::endl;
        if (Input::getKeyStatus(GLFW_KEY_K) == GLFW_PRESS)
            Generator::fillLineUntilTouchingRoad(*roadMap, intMouseWorldPos, CompassDirection::WEST);
        else
            roadMap->toggleFieldState(intMouseWorldPos);
    }

}

Scene::~Scene(){
}
