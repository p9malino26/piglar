#pragma once

#include "GLMIncludes.h"

//TODO possibly delete
#include "opengl/VertexArray.h"
#include "opengl/Buffer.h"
#include "opengl/Shader.h"


#include "Util.h"

class Camera;
class Display;


class Renderer {
    Shader shader;
    Buffer vbo;
    Buffer ebo;
    VertexArray vao;

    Camera* camera;
    Display* display;

    static constexpr char* vertexShaderSource = "res/shaders/vertexShader.glsl";
    static constexpr char* fragmentShaderSource = "res/shaders/fragmentShader.glsl";
    
    //singleton
    static Renderer* instance;
    
public:
    Renderer(Camera* camera, Display* display);
    /**
     * Renders a square 
     */
    void drawSquare(const glm::vec2& pos,float sideLength, const glm::vec3& color) const;
    void drawLine(const glm::vec2& pos, float length, CompassDirection dir);

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
