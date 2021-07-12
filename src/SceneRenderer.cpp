#include "SceneRenderer.h"

#include "TileMap.h"
#include "Scene.h"
#include "Renderer.h"
#include "generator/bottomuprectplacer.h"

#include "generator/RoadMapGen.h"

#include "SquareEntity.h"

class Pig: public SquareEntity {};
class Player: public SquareEntity {};
class Truck: public Entity {};

TexId pigTex;
TexId playerTex;
TexId truckTex;
TexId winTex;

SceneRenderer::SceneRenderer(const Scene* scene)
    :scene(scene)
{
    pigTex = Renderer::get()->initTexture("res/textures/cartoonpig.jpeg");
    playerTex = Renderer::get()->initTexture("res/textures/awesome-face.jpeg");
    truckTex = Renderer::get()->initTexture("res/textures/truck.jpeg");
    winTex = Renderer::get()->initTexture("res/textures/you-win.jpeg");
}

SceneRenderer::~SceneRenderer()
{
}

namespace  {
    void drawRoadMap(const TileMap& roadmap)
    {
        auto& renderer = *Renderer::get();

        for (int x = 0; x < roadmap.getWidth(); x++)
        {
            for (int y = 0; y < roadmap.getHeight() ; y++)
            {
                //set color white by default
                glm::vec3 color(0.0f, 1.0f, 1.0f);
                if( roadmap.getFieldState( glm::vec2i(x, y) ) ) //i.e it is black
                    color = glm::vec3(0.0f, 0.0f, 0.0f);

                renderer.setFillColor(color);
                Renderer::get()->drawSquare(glm::vec2(x, y), 1.0f);
            }

        }
    }

    void drawEntity(Entity& entity) // TODO Entity constness
    {
        Renderer::get()->drawRectangle(entity.getPos(), entity.getDims());
    }
}

void SceneRenderer::render ()
{
    auto& renderer = *Renderer::get();
    renderer.setWorldCoords(true);
    drawRoadMap(*(this->scene->getRoadMap()));
    auto& player = *scene->player;
    auto& pigs = const_cast<std::vector<Pig>&>(scene->pigs); //TODO this is an abomination!
    Truck& truck = *scene->truck;

    //draw player
    renderer.setFillTexture(playerTex);
    renderer.drawSquare(player.getPos(), player.getWidth());

    //draw pigs
    auto drawPig = [&renderer, this] (SquareEntity& p)
    {
        renderer.drawSquare(p.getPos(), p.getWidth());
    };

    renderer.setFillTexture(pigTex);
    for (auto& pig: pigs) drawPig(pig);

    //draw truck
    renderer.setFillTexture(truckTex);
    drawEntity(truck);

    if (scene->isWon()) {
        renderer.setWorldCoords(false);
        renderer.setFillTexture(winTex);
        renderer.drawSquare(RealPos(-0.5f, -0.5f), 1.f);
    }

}

const RealPos& Scene::getPlayerPos() {
    return player->getPos();
}
