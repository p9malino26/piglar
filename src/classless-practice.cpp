#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "opengl/Display.h"
#include "opengl/Buffer.h"
#include "opengl/VertexArray.h"
#include "opengl/Shader.h"
#include "opengl/Texture.h"

#include "TimeManager.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
float getPositiveSinTime();

int main()
{
    Display display("Textures", 800, 800);
    assert(display.good());

    glfwSetFramebufferSizeCallback(display.getRaw(), framebuffer_size_callback);

    float vertices[] = {
        // positions    // colors           // texture coords
         0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int eboVertices[] = {
        0, 1, 3,
        1, 2, 3
    };

    int offsets[3] = {2, 3, 2};

    VertexArray vao;
    Buffer vbo;
    Buffer ebo;
    Shader program;
    Texture pigTexture;
    
    vbo.init(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    ebo.init(GL_ELEMENT_ARRAY_BUFFER, eboVertices, sizeof(eboVertices));

    vao.bind();
    vbo.bind();
    ebo.bind();
    vao.specifyVertexAttributes(offsets, 3);


    program.init("res/shaders/vertexShader.glsl", "res/shaders/fragmentShader.glsl");
    program.use();
    assert(program.good());


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    pigTexture.init("pigfarming.jpg");
    pigTexture.bind();
    assert(pigTexture.good());

    pigTexture.activate(0);
    program.uniformInt("pigTex", 0);

    vao.bind();
    TimeManager::init();
    program.use();
    while (display.isOpen())
    {
        TimeManager::update();
        processInput(display.getRaw());
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        display.swapBuffers();

        display.checkEvents();

    }

}

float getPositiveSinTime()
{
    float sinTime = std::sin(static_cast<float>(glfwGetTime()));
    return sinTime * sinTime;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    //std::cout << "Window resized! Width: " << width << ", height: " << height << std::endl;
    glViewport(0, 0, width, height);
}
