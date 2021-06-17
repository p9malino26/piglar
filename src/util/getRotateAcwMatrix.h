#pragma once

#include "../GLMIncludes.h"
#include "CompassDirection.h"

constexpr glm::mat<2,2,int> getRotateAcwMatrix(int direction)
{
    direction = (direction + 4 % 4);
    switch (direction)
    {
    case 0:
        return {1, 0, 0, 1};
    case 1:
        return {0, 1, -1, 0};
    case 2:
        return {-1, 0, 0, 1};
    case 3:
        return {0, -1, 1, 0};

    }
}


