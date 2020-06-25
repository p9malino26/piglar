#include "Renderer.h"

#include "ResourceManager.h"

Renderer::Renderer(const Scene* _scene)
    :scene(_scene)
{

}

void Renderer::operator() (const glm::mat4& viewMatrix, const glm::mat4& projMatrix) const
{
    const RoadMap& roadmap = *(this->scene->getRoadMap());
    for (int x = 0; x < roadmap.getWidth(); x++)
    {
        for (int y = 0; y < roadmap.getHeight() ; y++)
        {
            //set color white by default
            glm::vec3 color(0.0f, 1.0f, 1.0f);
            if( roadmap.getFieldState( glm::vec2i(x, y) ) ) //i.e it is black
                color = glm::vec3(0.0f, 0.0f, 0.0f);

            squareRenderer(viewMatrix, projMatrix, glm::vec2(x, y), 1.0f, color);

        }

    }
}


