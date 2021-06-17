#pragma once

#include "GLMIncludes.h"

class Display;
class Camera;

class MouseManager
{
public:
    MouseManager(Display*, Camera*);
    glm::vec2 getWorldMousePos();
    inline static MouseManager* get() {return instance;}
private:
    static MouseManager* instance;
    Display* display;
    Camera* camera;
};