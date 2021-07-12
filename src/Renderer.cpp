#include <list>
#include <algorithm>

#include <glad/glad.h>
#include "Renderer.h"

#include "Camera.h"
#include "GLMIncludes.h"
#include "opengl/Display.h"

#include "util/line.h"
#include "util/compassUtil.h"
#include "opengl/VertexArray.h"
#include "opengl/Buffer.h"
#include "opengl/Shader.h"
#include "opengl/Texture.h"

#define TEXTURE_SLOT 0

Renderer* Renderer::instance;

const char* Renderer::vertexShaderSource   = "res/shaders/vertexShader.glsl";
const char* Renderer::fragmentShaderSource = "res/shaders/fragmentShader.glsl";

void getLinesForRectangle(std::list<Line>& lineList, const PosRectangle& square);

constexpr glm::mat4 ID4 = glm::mat4(1);

Renderer::Renderer(Camera* camera, Display* display)
    :shader(new Shader(vertexShaderSource, fragmentShaderSource)), camera(camera), display(display), vao(new VertexArray())
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

    vbo = std::make_unique<Buffer>(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    ebo = std::make_unique<Buffer>(GL_ELEMENT_ARRAY_BUFFER, eboVertices, sizeof(eboVertices));

    vao->bind();
    vbo->bind();
    vao->specifyVertexAttributes(offsets, 1);
    ebo->bind();

    shader->use();

    shader->uniformInt("theTexture", TEXTURE_SLOT);

    textures.reserve(16);
    setWorldCoords(true);
}

//@todo sort out implementation
void Renderer::drawSquare (const glm::vec2& pos, float sideLength)
{
    drawRectangle(pos, {sideLength, sideLength});
}


void Renderer::drawRectangleWithLines(const PosRectangle& rect, const glm::vec3& rectColor, const glm::vec3& lineColor) {
    drawRectangle(rect.pos, rect.dims);
    std::list<Line> rectLines;
    getLinesForRectangle(rectLines, rect);
    std::for_each(rectLines.begin(), rectLines.end(), [this] (const Line& l) {drawLine(l);});
}


void Renderer::drawLine(const Line &line) //deprecated
{
    //TODO this contains duplicated code and needs tidying

    glm::mat4 modelMatrix(1.0f);
    //model matrix: scale for length, rotate and place
    //place
    modelMatrix = glm::translate(modelMatrix, glm::vec3(line.pos, 0.0f));
    //rotate
    modelMatrix = glm::rotate(modelMatrix, -glm::radians(static_cast<float>(clockwiseDirectionAngle(line.direction))), glm::vec3(0.f,0.f,1.f));
    //scale
    modelMatrix = glm::scale(modelMatrix, glm::vec3(line.length, line.length, 1.0f));

    shader->uniformMat4("model", modelMatrix);

    glDrawArrays(GL_LINES, 2, 2);

}

void Renderer::init(Camera *camera, Display *display) {
    instance = new Renderer(camera, display);
}

Renderer::~Renderer() {
}

void Renderer::drawRectangle(const glm::vec2& pos, const glm::vec2& dims)
{
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(pos, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(dims.x, dims.y, 1.0f));

    shader->uniformMat4("model", modelMatrix);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::setWorldCoords(bool isWorld) {
    if (isWorld) {
        const auto& viewMatrix = camera->getViewMatrix();
        const auto& projMatrix = display->getProjectionMatrix();

        shader->uniformMat4("view", viewMatrix);
        shader->uniformMat4("proj", projMatrix);

    } else {
        shader->uniformMat4("view", ID4);
        shader->uniformMat4("proj", ID4);
    }
}

TexId Renderer::initTexture(const std::string &fname)
{
    textures.emplace_back(fname);
    return textures.size() - 1;
}

void Renderer::setFillTexture(TexId textureId)
{
    auto& theTexture = textures[textureId];
    theTexture.activate(TEXTURE_SLOT);
    shader->uniformInt("showTexture", true);
}

void Renderer::setFillColor(const Color &color)
{
    shader->uniformVec3("inColor", color);
    shader->uniformInt("showTexture", false);
}


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

