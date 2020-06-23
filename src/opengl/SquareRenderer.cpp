#include "SquareRenderer.h"



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#include "opengl.h"
#include "../Util.h"

const std::string SquareRenderer::vertexShaderPath   = "./data/shaders/squareVertexShader.glsl";
const std::string SquareRenderer::fragmentShaderPath = "./data/shaders/squareFragmentShader.glsl";


SquareRenderer::SquareRenderer()
    :m_shader(vertexShaderPath, fragmentShaderPath)
{
}

void SquareRenderer::render() const
{
    //glCheckError();
    m_shader.use();
    m_square.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6 );
    m_square.unbind();

    
}
