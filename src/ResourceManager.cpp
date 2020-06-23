#include "ResourceManager.h"



ResourceManager::ResourceManager()
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

    vao = std::make_unique<VertexArray>();
    vbo = std::make_unique<Buffer>( GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    ebo = std::make_unique<Buffer>( GL_ELEMENT_ARRAY_BUFFER, eboVertices, sizeof(eboVertices));
    shader = std::make_unique<Shader>("res/shaders/vertexShader.glsl", "res/shaders/fragmentShader.glsl");

    vao->bind();
    vbo->bind();
    vao->specifyVertexAttributes(offsets, 1);
    ebo->bind();
    vao->unbind();
        
}
