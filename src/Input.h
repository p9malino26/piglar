#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#include "GLMIncludes.h"

class Input
{
public:
    //enum KeyEvent {NONE, RELEASED, PRESSED, REPREAT};
    friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
private:
    static GLFWwindow* window;
    static float _yScrollDelta;
    static bool has_scrolled;
    static const int keysSize = 349;
    static int keys[keysSize];
public:
    static bool mouseClicked;

    static void update();
    static void init(GLFWwindow* window);
    inline static int getKeyStatus(int key) { return glfwGetKey(window, key); }
    inline static int getKeyEvent(int key) {return keys[key] - 1;}
    inline static int keyInfo(int key, int status) { return getKeyStatus(key) == status; } // deprecated
    inline static float yScrollDelta() { return _yScrollDelta;}
    static glm::vec2 getMousePos();
    inline static bool mouseHasClicked() { return mouseClicked; }
};


#endif
