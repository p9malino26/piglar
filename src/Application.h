#ifndef APPLICATION_H
#define APPLICATION_H


#include "opengl/Display.h"

class Application
{
public:
    Application(const std::string& title, int windowWidth, int windowHeight);
    ~Application();
    void runMainLoop();
protected:
    Display display;

    virtual void processFrame() = 0;
private:
    static constexpr int GL_CONTEXT_VERSION_MAJOR = 4;
    static constexpr int GL_CONTEXT_VERSION_MINOR = 5;


    void processInput();


};

#endif // APPLICATION_H
