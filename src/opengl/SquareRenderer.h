#ifndef SQUARERENDERER_H
#define SQUARERENDERER_H

/**
 * @todo write docs
 */

//#define GLEW_STATIC

#include <memory>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProg.h"
#include "Shape.h"

class SquareRenderer
{

    Square m_square;
    ShaderProg m_shader;

    
    static const std::string vertexShaderPath;
    static const std::string fragmentShaderPath;
    
    
public:
    SquareRenderer();
    void render() const;
    const ShaderProg& getShaderProg() const { return m_shader;}
    
};

#endif // SQUARERENDERER_H
