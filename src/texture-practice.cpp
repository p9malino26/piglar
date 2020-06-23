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
    
    vbo.init(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    ebo.init(GL_ELEMENT_ARRAY_BUFFER, eboVertices, sizeof(eboVertices));

    vao.bind();
    vbo.bind();
    ebo.bind();
    vao.specifyVertexAttributes(offsets, 3);
    vao.unbind();

    Shader program;
    program.init("res/shaders/vertexShader.glsl", "res/shaders/fragmentShader.glsl");
    assert(program.good());


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Texture pigTexture;
    pigTexture.init("pigfarming.jpg");
    assert(pigTexture.good());
    Texture crateTexture;
    crateTexture.init("crate.jpg");
    assert(crateTexture.good());

    pigTexture.activate(0);
    crateTexture.activate(1);

    vao.bind();
    TimeManager::init();
    program.use();
    while (display.isOpen())
    {
        TimeManager::update();
        processInput(display.getRaw());

        //draw square 1

        glm::mat4 trans(1.f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, -2 * TimeManager::time(), glm::vec3(0.f, 0.f, 1.f));
        trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 1.0f));


        //bind texture

        program.uniformInt("theTexture", 0);
        program.uniformMat4("model", trans);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //draw square 2

        trans = glm::mat4(1.f);
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        trans = glm::rotate(trans,  TimeManager::time(), glm::vec3(0.f, 0.f, 1.f));
        trans = glm::scale(trans, glm::vec3(0.7f, 0.7f, 1.0f));

        //bind texture

        program.uniformInt("theTexture", 1);
        program.uniformMat4("model", trans);


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
