#include "SceneRenderer.h"

#include "RoadMap.h"
#include "Scene.h"
#include "Renderer.h"
#include "generator/rectangleplacementrecorder.h"

SceneRenderer::SceneRenderer(const Scene* scene)
    :scene(scene)
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

    void drawLines(const std::list<Line>& lines)
    {
        for(Line line: lines) {
            Renderer::get()->drawLine(line);
        }
    }
}

void SceneRenderer::render () const
{
    drawRoadMap(*(this->scene->getRoadMap()));
    drawLines(scene->rpr->lines);
}
