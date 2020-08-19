#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"



#include "Util.h"
#include "TimeManager.h"
#include "Input.h"
#include "Random.h"

Application::Application(const std::string& title, int windowWidth, int windowHeight)
    :display(title, windowWidth, windowHeight, GL_CONTEXT_VERSION_MAJOR, GL_CONTEXT_VERSION_MINOR)
{
    Input::init(display.getRaw());
    TimeManager::init();
    Random::init();
}

void Application::runMainLoop()
{
    while(display.isOpen())
    {
        TimeManager::update();
        Input::update();
        processInput();
        processFrame();
        display.swapBuffers();

    }
}

void Application::processInput()
{
    if(Input::getKeyStatus(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(display.getRaw(), true);
}

