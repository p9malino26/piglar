#ifndef RENDERER_H 
#define RENDERER_H

#include <glad/glad.h>

#include "SquareRenderer.h"
#include "Scene.h"

class Renderer
{
    SquareRenderer squareRenderer;

    const Scene* scene;
public:
    explicit Renderer(const Scene*);
    /**
     * renders the scene
     */
    void render (const glm::mat4& viewMatrix, const glm::mat4& projMatrix) const;
};

#endif
