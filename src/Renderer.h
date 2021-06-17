#pragma once

#include "GLMIncludes.h"

//TODO possibly delete
#include "opengl/VertexArray.h"
#include "opengl/Buffer.h"
#include "opengl/Shader.h"


#include "util/CompassDirection.h"
#include "util/PosRectangle.h"

class Camera;
class Display;
class Line;


class Renderer {
    Shader shader;
    Buffer vbo;
    Buffer ebo;
    VertexArray vao;

    Camera* camera;
    Display* display;

    static const char* vertexShaderSource  ;
    static const char* fragmentShaderSource;
    
    //singleton
    static Renderer* instance;
    
public:
    Renderer(Camera* camera, Display* display);
    /**
     * Renders a square 
     */
    void drawSquare(const glm::vec2& pos,float sideLength, const glm::vec3& color) const;
    void drawRectangle(const PosRectangle& rect, const glm::vec3& color);
    void drawRectangleWithLines(const PosRectangle& rect, const glm::vec3& rectColor, const glm::vec3& lineColor);
    void drawLine(const Line &line);

    //singleton
    template<typename ... Args>
    static void init(Args&&... args) {
        instance = new Renderer(std::forward<Args>(args) ...);
    }

    static inline Renderer* get()
    {
        return instance;
    }

    static inline void destroy()
    {
        delete instance;
    }
};
