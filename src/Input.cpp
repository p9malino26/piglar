#include <iostream>
#include <cstring>

#include "Input.h"

#include "TimeManager.h"



GLFWwindow* Input::window;
float Input::_yScrollDelta;
bool Input::has_scrolled;
int Input::keys[keysSize]  {};
bool Input::mouseClicked = false;
//const int Input::keysSize = 349;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void Input::init(GLFWwindow* _window)
{
    window = _window;
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
    {
        if(button == 0 && action == GLFW_PRESS)
            Input::mouseClicked = true;
    });
    

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
    Input::_yScrollDelta = yoffset;
    Input::has_scrolled = true;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::keys[key] = action + 1;
}

