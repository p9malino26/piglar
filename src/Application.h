#ifndef APPLICATION_H
#define APPLICATION_H

#include <glad/glad.h>


#include "opengl/Display.h"

#include "Camera.h"
#include "ResourceManager.h"

class Application
{
public:
    Application();
    void runMainLoop();
protected:
    Display display;
    ResourceManager resourceManager;
    Camera camera;

    virtual void processFrame() = 0;
private:


    void processInput();


};

#endif // APPLICATION_H
