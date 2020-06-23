#pragma once

#include "GLMIncludes.h"

class Square
{

    float m_width;
    glm::vec2 m_position;
    glm::vec3 m_color;
public:
    Square();
    void update();
    inline glm::vec2& getPosition()
    {
        return m_position;
    }

    inline float getWidth()
    {
        return m_width;
    }

    inline void changeXpos(float delta)
    {
        m_position.x += delta;
    }

    inline void changeYpos(float delta)
    {
        m_position.y += delta;
    }

    inline void setPosition(const glm::vec2& _position)
    {
        m_position = _position;
    }

    void draw();



};