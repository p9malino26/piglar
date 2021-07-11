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
    Input::instance->mouseKeys[button] = action + 1;
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

    //set all keys (keyboard and mouse) to zero
    std::memset(keys, 0, (keysSize + mouseKeysSize) * sizeof(int));
    glfwPollEvents();

    updateMousePos();
    if (getMouseButtonEvent(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        m_dragging = true;
        mouseClicked = true;
    }

    if (getMouseButtonEvent(GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        m_dragging = false;
}

glm::vec2 Input::updateMousePos()
{
    double x,y;
    glfwGetCursorPos(window, &x, &y);
    lastMousePos = currentMousePos;
    currentMousePos = glm::vec2(static_cast<float>(x), static_cast<float>(y));
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

RealPos Input::getDragDelta() {
    if (m_dragging)
        return getMouseDelta();
    else return RealPos(0.f);
}



