#include "Renderer.h"

#include "Camera.h"
#include "GLMIncludes.h"
#include "opengl/Display.h"

Renderer* Renderer::instance;

Renderer::Renderer(Camera* camera, Display* display)
    :shader(vertexShaderSource, fragmentShaderSource), camera(camera), display(display)
{
    float vertices[] = {
        // positions
         1.0f,  1.0f,  // top right
         1.0f,  0.0f,  // bottom right
         0.0f,  0.0f,  // bottom left
         0.0f,  1.0f  // top left 
    };

    unsigned int eboVertices[] = {
        1, 0, 3,
        1, 2, 3
    };

    int offsets[2] = {2};

    vbo.init(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    ebo.init(GL_ELEMENT_ARRAY_BUFFER, eboVertices, sizeof(eboVertices));
    
    vao.bind();
    vbo.bind();
    vao.specifyVertexAttributes(offsets, 1);
    ebo.bind();
    vao.unbind();
}

//@todo sort out implementation
void Renderer::drawSquare (const glm::vec2& pos, float sideLength, const glm::vec3& color) const
{
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(pos, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(sideLength, sideLength, 1.0f));
    
    const auto& viewMatrix = camera->getViewMatrix();
    const auto& projMatrix = display->getProjectionMatrix();

    shader.use();
    shader.uniformMat4("model", modelMatrix);
    shader.uniformMat4("view", viewMatrix);
    shader.uniformMat4("proj", projMatrix);

    shader.uniformVec3("uColor", color);

    vao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao.unbind();
    shader.unUse();

    
}
