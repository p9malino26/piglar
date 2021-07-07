#pragma once

#include "GLMIncludes.h"
#include "util/singleton.h"
#include "vectors.h"

class Display;
class Camera;

class MouseManager: public Singleton
{
public:
    glm::vec2 getWorldMousePos();

    void update();
    RealPos mouseToWorld(RealPos mouseVec);
SINGLETON(MouseManager)
    static void init(Display*, Camera*);
private:
    MouseManager(Display*, Camera*); // TODO refactor singleton
    Display* display;
    Camera* camera;
};