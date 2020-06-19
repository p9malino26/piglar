#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Rectangle
{
public:
    Rectangle();
    const glm::vec3& position() { return position; }
private:
    
    glm::vec3 position;

};

#endif // RECTANGLE_H
