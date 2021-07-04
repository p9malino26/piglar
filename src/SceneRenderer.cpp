#include "SceneRenderer.h"

#include "TileMap.h"
#include "Scene.h"
#include "Renderer.h"
#include "util/Random.h"
#include "generator/bottomuprectplacer.h"

#include "generator/RoadMapGen.h"

#include "SquarePlayer.h"



SceneRenderer::SceneRenderer(const Scene* scene)
    :scene(scene)
{
    pigTex = Renderer::get()->initTexture("res/textures/cartoonpig.jpeg");
    playerTex = Renderer::get()->initTexture("res/textures/awesome-face.jpeg");
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

}

void SceneRenderer::render ()
{
    auto& renderer = *Renderer::get();

    drawRoadMap(*(this->scene->getRoadMap()));
    auto& player = *scene->player;
    auto& pigs = const_cast<std::vector<SquarePlayer>&>(scene->pigs); //TODO this is an abomination!

    renderer.setFillTexture(playerTex);
    renderer.drawSquare(player.getPos(), player.getWidth());

    auto drawPig = [&renderer, this] (SquarePlayer& p)
    {
        renderer.setFillTexture(pigTex);
        renderer.drawSquare(p.getPos(), p.getWidth());

    };

    renderer.setFillColor({1.f, 0.64f, 0.43f});
    for (auto& pig: pigs) drawPig(pig);
}
