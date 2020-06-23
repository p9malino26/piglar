#include "Application.h"

#include "opengl/Display.h"
#include "opengl/Buffer.h"
#include "opengl/VertexArray.h"
#include "opengl/Shader.h"
#include "opengl/Texture.h"

#include "ResourceManager.h"
#include "RoadMap.h"
#include "Camera.h"
#include "Input.h"
#include "GLMIncludes.h"
#include "TimeManager.h"
#include "Sprite.h"

void renderSquare(ResourceManager& resourceManager, const glm::vec2& position, float sideLength, const glm::vec3& color, const glm::mat4& viewMat, const glm::mat4& projMat);

class TestApp: public Application
{
    RoadMap roadmap;
    Sprite sprite;

    glm::mat4 viewMatrix;
    glm::mat4 projMatrix;

    void processInput();

    void processFrame() override;
    void drawRoadMap();
    void drawSprite();

public:
    TestApp();

};

TestApp::TestApp()
{
    camera.setPosition(glm::vec2(9.0f, 9.0f));
    sprite.setPosition(glm::vec2(3.0f, 4.0f));
}

void TestApp::processFrame()
{
    processInput();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    viewMatrix = camera.getViewMatrix();
    projMatrix = display.getProjectionMatrix();

    camera.update();
    sprite.update();
    drawRoadMap();
    drawSprite();


}

void TestApp::drawRoadMap()
{
    resourceManager.vao->bind();
    for(int x = 0; x < roadmap.width() ; x++)
    {
        for (int y = 0; y < roadmap.height() ; y++)
        {
            //set color
            
            if(roadmap.at(x, y) == RoadMap::TileColour::WHITE) 
                renderSquare(resourceManager, glm::vec2(x, y), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), viewMatrix, projMatrix);
            else
                renderSquare(resourceManager, glm::vec2(x, y), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), viewMatrix, projMatrix);

        }

    }
}

void TestApp::drawSprite()
{
    renderSquare(resourceManager, sprite.getPosition(), 0.7f, glm::vec3(1.0f, 0.0f, 0.0f), viewMatrix, projMatrix);
}

void TestApp::processInput()
{
    if(Input::getKeyEvent(GLFW_KEY_U) == GLFW_PRESS) 
    {
        roadmap.updateGenNodes();
    }
}

void renderSquare(ResourceManager& resourceManager, const glm::vec2& position, float sideLength, const glm::vec3& color, const glm::mat4& viewMat, const glm::mat4& projMat)
{
    glm::mat4 modelMat(1.0f);
    modelMat = glm::translate(modelMat, glm::vec3(position, 0.0f));
    modelMat = glm::scale(modelMat, glm::vec3(sideLength, sideLength, 1.0f));
    

    resourceManager.shader->use();
    resourceManager.shader->uniformMat4("model", modelMat);
    resourceManager.shader->uniformMat4("view", viewMat);
    resourceManager.shader->uniformMat4("proj", projMat);

    resourceManager.shader->uniformVec3("uColor", color);

    resourceManager.vao->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    resourceManager.vao->unbind();
    //resourceManager.shader->unUse();
}

int main()
{
    TestApp app;
    app.runMainLoop();
    return 0;
}
