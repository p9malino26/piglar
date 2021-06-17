#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace glm
{
    typedef glm::vec<2, int, defaultp> vec2i;


    //tested
    template <typename T>
    constexpr glm::vec<2, T, defaultp> swap(const glm::vec<2, T, defaultp>& vec)
    {
        return {vec.y, vec.x};
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const glm::vec<2, T, glm::defaultp>& vec)
{
    return os << '(' << vec.x << ", " << vec.y << ')';
}
