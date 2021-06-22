#include <iostream>
#include <cstring>
#include <functional>

#include "Input.h"

#include "TimeManager.h"

Input* Input::instance;
//const int Input::keysSize = 349;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == 0 && action == GLFW_PRESS)
        Input::instance->mouseClicked = true;
};

Input::Input(GLFWwindow* _window)
{
    window = _window;
}

void Input::init(GLFWwindow* window)
{
    instance = new Input(window);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);
}

void Input::update()
{
    if (has_scrolled) 
    {
        has_scrolled = false;
        _yScrollDelta = 0.0f;
    }

    mouseClicked = false;

    //set all keys to zero
    std::memset(keys, 0, keysSize * sizeof(int));
    glfwPollEvents();
}

glm::vec2 Input::getMousePos()
{
    double x,y;
    glfwGetCursorPos(window, &x, &y);
    return glm::vec2(static_cast<float>(x), static_cast<float>(y));
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Input::instance->_yScrollDelta = yoffset;
    Input::instance->has_scrolled = true;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::instance->keys[key] = action + 1;
}



