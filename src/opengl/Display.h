#pragma once

#include <GLFW/glfw3.h>

#include "../GLMIncludes.h"

#include <iostream>
#include <string>


class Display
{
public:
    Display( const std::string& title, int width = 800, int height = 600, int contextVersionMajor = 3, int contextVersionMinor = 2);
    ~Display();
    void checkEvents() const;
    //void clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const; // deprecated
    //void clear() const;
    void swapBuffers() const;
    bool isOpen() const;
    void close() const;

    glm::mat4 getProjectionMatrix();
    /**
     * Returns a matrix transforming the Normalized Device Coordinates into pixel co-ordinates
     * */
    glm::mat4 getPixelMatrix();
    
    inline int width() const {return m_width; }
    inline int height() const {return m_height; }
    inline GLFWwindow* getRaw() const {return m_window; }
    inline bool good() const {return m_good; }


private:
    int m_width, m_height;
    std::string m_title;
    bool m_good;
    //unsigned int m_states; // this member will hold the states of the display. 1st bit is whether the window is generally good or not. 2nd bit is whether glfw has initialized successfully. 3rd bit is whether window is good or not
    GLFWwindow* m_window;

};


