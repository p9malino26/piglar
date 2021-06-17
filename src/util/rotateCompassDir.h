#pragma once

#include "CompassDirection.h"

constexpr CompassDirection rotateAcw(CompassDirection dir, int factor)
{
    return CompassDirection( ( (int)dir - factor + 4) % 4);
}
