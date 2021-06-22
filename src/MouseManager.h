#pragma once

#include "GLMIncludes.h"
#include "util/singleton.h"

class Display;
class Camera;

class MouseManager: public Singleton
{
public:
    glm::vec2 getWorldMousePos();

    SINGLETON(MouseManager)
    static void init(Display*, Camera*);
private:
    MouseManager(Display*, Camera*);
    Display* display;
    Camera* camera;
};