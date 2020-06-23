#pragma once

#include "GLMIncludes.h"

class Display;
class Camera;

class MouseManager
{
public:
    MouseManager(Display*, Camera*);
    glm::vec2 getWorldMousePos();
private:
    Display* display;
    Camera* camera;
};