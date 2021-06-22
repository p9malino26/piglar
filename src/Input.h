#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#include "GLMIncludes.h"
#include "util/singleton.h"

class Input: public Singleton
{
public:
    friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    friend void mouse_callback(GLFWwindow* window, int button, int action, int mods);
private:
    GLFWwindow* window;
    float _yScrollDelta;
    bool has_scrolled;
    static const int keysSize = 349;
    int keys[keysSize];

    Input(GLFWwindow* window);
public:
    bool mouseClicked;

    void update();
    inline int getKeyStatus(int key) { return glfwGetKey(window, key); }
    inline int getKeyEvent(int key) {return keys[key] - 1;}
    inline int keyInfo(int key, int status) { return getKeyStatus(key) == status; } // deprecated
    inline float yScrollDelta() { return _yScrollDelta;}
    glm::vec2 getMousePos();
    inline bool mouseHasClicked() { return mouseClicked; }

SINGLETON(Input)
    static void init(GLFWwindow* window);
};


#endif
