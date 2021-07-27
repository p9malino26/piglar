#pragma once

#include "util/vectors.h"
#include "util/singleton.h"
#include "util/vectors.h"

class Display;
class Camera;

class MouseManager: public Singleton
{
public:
    MouseManager();
    glm::vec2 getWorldMousePos();

    void update();
    RealPos mouseToWorld(RealPos mouseVec);
SINGLETON(MouseManager)
};