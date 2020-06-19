#ifndef SQUARERENDERER_H
#define SQUARERENDERER_H

#include "GLMIncludes.h"

#include "opengl/VertexArray.h"
#include "opengl/Buffer.h"
#include "opengl/Shader.h"



class SquareRenderer {
    Shader shader;
    Buffer vbo;
    Buffer ebo;
    VertexArray vao;

    static constexpr char* vertexShaderSource = "res/shaders/vertexShader.glsl";
    static constexpr char* fragmentShaderSource = "res/shaders/fragmentShader.glsl";
    
    
public:
    SquareRenderer();
    /**
     * Renders a square 
     */
    void operator() (const glm::mat4& viewMatrix, const glm::mat4& projMatrix, const glm::vec2& pos, float sideLength, const glm::vec3& color) const;    
};

#endif // SQUARERENDERER_H
