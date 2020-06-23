#include <iostream>
#include <cstring>

#include "Input.h"

#include "TimeManager.h"



GLFWwindow* Input::window;
float Input::_yScrollDelta;
bool Input::has_scrolled;
int Input::keys[keysSize]  {};
//const int Input::keysSize = 349;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void Input::init(GLFWwindow* _window)
{
    window = _window;
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    

}

void Input::update()
{
    if (has_scrolled) 
    {
        has_scrolled = false;
        _yScrollDelta = 0.0f;
    }

    std::memset(keys, 0, keysSize * sizeof(int));
    glfwPollEvents();

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