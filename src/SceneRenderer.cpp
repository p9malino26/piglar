#include "SceneRenderer.h"

#include "RoadMap.h"
#include "Scene.h"
#include "Renderer.h"
#include "util/Random.h"
#include "generator/bottomuprectplacer.h"

#include "generator/RoadMapGen.h"

#include "SquarePlayer.h"

SceneRenderer::SceneRenderer(const Scene* scene)
    :scene(scene)
{
}

SceneRenderer::~SceneRenderer()
{
}

namespace  {
    void drawRoadMap(const RoadMap& roadmap)
    {
        for (int x = 0; x < roadmap.getWidth(); x++)
        {
            for (int y = 0; y < roadmap.getHeight() ; y++)
            {
                //set color white by default
                glm::vec3 color(0.0f, 1.0f, 1.0f);
                if( roadmap.getFieldState( glm::vec2i(x, y) ) ) //i.e it is black
                    color = glm::vec3(0.0f, 0.0f, 0.0f);

                Renderer::get()->drawSquare(glm::vec2(x, y), 1.0f, color);
            }

        }
    }

}

void SceneRenderer::render () const
{
    drawRoadMap(*(this->scene->getRoadMap()));
    auto& player = *scene->player;
    auto& chaser = *scene->chaser;
    Renderer::get()->drawSquare(player.getPos(), player.getWidth(), {0.f, 0.f, 1.f});
    Renderer::get()->drawSquare(chaser.getPos(), chaser.getWidth(), {1.f, 0.f, 1.f});
}
