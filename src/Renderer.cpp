#include <list>
#include <algorithm>

#include "Renderer.h"

#include "Camera.h"
#include "GLMIncludes.h"
#include "opengl/Display.h"

#include "util/line.h"
#include "util/compassUtil.h"

Renderer* Renderer::instance;

const char* Renderer::vertexShaderSource   = "res/shaders/vertexShader.glsl";
const char* Renderer::fragmentShaderSource = "res/shaders/fragmentShader.glsl";

void getLinesForRectangle(std::list<Line>& lineList, const PosRectangle& square){
    auto varPos = square.pos;
    auto& dims = square.dims;
    //left
    lineList.emplace_back(varPos, dims.y, CompassDirection::NORTH);
    //top
    varPos.y += dims.y;
    lineList.emplace_back(varPos, dims.x, CompassDirection::EAST);
    //right
    varPos.x += dims.x;
    lineList.emplace_back(varPos, dims.y, CompassDirection::SOUTH);
    //bottom
    varPos.y -= dims.y;
    lineList.emplace_back(varPos, dims.x, CompassDirection::WEST);
}


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

void Renderer::drawRectangle(const PosRectangle& rect, const glm::vec3& color) {
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(rect.pos, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(rect.dims.x, rect.dims.y, 1.0f));

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

void Renderer::drawRectangleWithLines(const PosRectangle& rect, const glm::vec3& rectColor, const glm::vec3& lineColor) {
    drawRectangle(rect, rectColor);
    std::list<Line> rectLines;
    getLinesForRectangle(rectLines, rect);
    std::for_each(rectLines.begin(), rectLines.end(), [this] (const Line& l) {drawLine(l);});


}

void Renderer::drawLine(const Line &line)
{
    //TODO this contains duplicated code and needs tidying
    glm::vec3 color {0.871f,0.278f,0.886f};

    glm::mat4 modelMatrix(1.0f);
    //model matrix: scale for length, rotate and place
    //place
    modelMatrix = glm::translate(modelMatrix, glm::vec3(line.pos, 0.0f));
    //rotate
    modelMatrix = glm::rotate(modelMatrix, -glm::radians(static_cast<float>(clockwiseDirectionAngle(line.direction))), glm::vec3(0.f,0.f,1.f));
    //scale
    modelMatrix = glm::scale(modelMatrix, glm::vec3(line.length, line.length, 1.0f));

    const auto& viewMatrix = camera->getViewMatrix();
    const auto& projMatrix = display->getProjectionMatrix();

    shader.use();
    shader.uniformMat4("model", modelMatrix);
    shader.uniformMat4("view", viewMatrix);
    shader.uniformMat4("proj", projMatrix);

    shader.uniformVec3("uColor", color);


    vao.bind();
    glDrawArrays(GL_LINES, 2, 2);

}

void Renderer::init(Camera *camera, Display *display) {
    instance = new Renderer(camera, display);
}
