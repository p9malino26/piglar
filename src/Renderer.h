#pragma once

#include <memory>

#include "GLMIncludes.h"

#include "util/CompassDirection.h"
#include "util/PosRectangle.h"
#include "util/singleton.h"

class Camera;
class Display;
class Line;

class Shader;
class Buffer;
class VertexArray;

class Renderer: public Singleton {
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Buffer> vbo;
    std::unique_ptr<Buffer> ebo;
    std::unique_ptr<VertexArray> vao;

    Camera* camera;
    Display* display;

    static const char* vertexShaderSource;
    static const char* fragmentShaderSource;
    
    //singleton

    Renderer(Camera* camera, Display* display);

public:
    virtual ~Renderer();

public:
    /**
     * Renders a square 
     */
    void drawSquare(const glm::vec2& pos,float sideLength, const glm::vec3& color) const;
    void drawRectangle(const PosRectangle& rect, const glm::vec3& color);
    void drawRectangleWithLines(const PosRectangle& rect, const glm::vec3& rectColor, const glm::vec3& lineColor);
    void drawLine(const Line &line);

    //singleton
SINGLETON(Renderer)
    static void init(Camera* camera, Display* display);

};
