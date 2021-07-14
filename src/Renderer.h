#pragma once

#include <memory>
#include <vector>

#include "vectors.h"

#include "util/CompassDirection.h"
#include "util/PosRectangle.h"
#include "util/singleton.h"

#include "TexId.h"

class Camera;
class Display;
class Line;

class Shader;
class Buffer;
class VertexArray;
class Texture;

typedef glm::vec3 Color;

class Renderer: public Singleton {
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Buffer> vbo;
    std::unique_ptr<Buffer> ebo;
    std::unique_ptr<VertexArray> vao;

    std::vector<Texture> textures;

    static const char* vertexShaderSource;
    static const char* fragmentShaderSource;
    
public:
    Renderer();
    ~Renderer();

    void setWorldCoords(bool);

    TexId initTexture(const std::string& fname);

    void setFillTexture(TexId textureId);
    void setFillColor(const Color& color);

    void drawRectangle(const glm::vec2& pos, const glm::vec2& dims);
    void drawSquare(const glm::vec2& pos,float sideLength);
    //deprecated
    void drawRectangleWithLines(const PosRectangle& rect, const glm::vec3& rectColor, const glm::vec3& lineColor);
    void drawLine(const Line &line);

    //singleton
SINGLETON(Renderer)
};
