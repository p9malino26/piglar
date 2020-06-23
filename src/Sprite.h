#ifndef SPRITE_H
#define SPRITE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Sprite
{

    float width;
    float speed;
    glm::vec2 position;
public:
    Sprite();
    void update();
    inline glm::vec2& getPosition()
    {
        return position;
    }

    inline float getWidth()
    {
        return width;
    }

    inline void changeXpos(float delta)
    {
        position.x += delta;
    }

    inline void changeYpos(float delta)
    {
        position.y += delta;
    }

    inline void setPosition(const glm::vec2& _position)
    {
        position = _position;
    }



};

#endif
