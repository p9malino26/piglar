#include "Rectangle.h"

#include "opengl/VertexBuffer.h"
#include "opengl/IndexBuffer.h"

#include <glad/glad.h>

Rectangle::Rectangle()
    :shader("data/shaders/rectangleVert.glsl", "data/shaders/rectangleFrag.glsl")
{

    float vertices[16] = {
        // positions  // texture coords
         0.5f,  0.5f,  1.0f, 1.0f,   // top right
         0.5f, -0.5f,  1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f,  0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f,  0.0f, 1.0f    // top left
    };

    unsigned int eboVertices[] = {
        0, 1, 3,
        1, 2, 3
    };

    int offsets[] = {2,2};

    vao.bind();
    VertexBuffer vbo(vertices, 16 * sizeof(float), offsets, 2);
    IndexBuffer ebo(eboVertices, 6);
    vao.unbind();


}

/*

    float deltaDistance = speed * TimeManager::deltaTime();
    if (keyInfo(GLFW_KEY_ESCAPE, GLFW_PRESS)) display.close();
    if(keyInfo(GLFW_KEY_W, GLFW_PRESS)) position += deltaDistance * up;
    if(keyInfo(GLFW_KEY_A, GLFW_PRESS)) position -= deltaDistance * right;
    if(keyInfo(GLFW_KEY_S, GLFW_PRESS)) position -= deltaDistance * up;
    if(keyInfo(GLFW_KEY_D, GLFW_PRESS)) position += deltaDistance * right;
    if(keyInfo(GLFW_KEY_R, GLFW_PRESS)) position = glm::vec3(0.0f, 0.0f, 0.0f);
*/
