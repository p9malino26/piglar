#include "SceneRenderer.h"

#include "RoadMap.h"
#include "Scene.h"
#include "Renderer.h"
#include "util/Random.h"
#include "generator/bottomuprectplacer.h"

#include "generator/RoadMapGen.h"

SceneRenderer::SceneRenderer(const Scene* scene)
    :scene(scene), rpr(new BottomUpRectPlacer(100,100))
{
    while (true) {
        Rectangle rect{Random::randInt(7,20), Random::randInt(7,20)};
        auto insertPos = rpr->placeRectangle(rect);
        if (!insertPos.has_value()) break;
        rectData.push_back({insertPos.value(), (glm::vec2i&)rect});
    }
}

SceneRenderer::~SceneRenderer()
{
    delete rpr;
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

    void drawLines(const std::list<Line>& lines)
    {
        for(Line line: lines) {
            Renderer::get()->drawLine(line);
        }
    }
}

void SceneRenderer::render () const
{
    /*drawRoadMap(*(this->scene->getRoadMap()));
    auto& lines = scene->roadMapGen->rpr->envelopeLines;
    drawLines(lines);*/
    for (auto& rect_pos: rectData)
    {
        Renderer::get()->drawRectangleWithLines(rect_pos, glm::vec3(1,1,0), glm::vec3(0,1,1));
    }
}
