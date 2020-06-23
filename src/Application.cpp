#include "Application.h"
#include "ResourceManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Util.h"
#include "TimeManager.h"
#include "Input.h"
#include "Random.h"

Application::Application()
    :display("Piglar!", 800, 600, 4, 5)
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

