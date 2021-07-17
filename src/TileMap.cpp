#include "TileMap.h"

#include "util/compassVec.h"

TileMap::TileMap(int width, int height)
    :width(width), height(height), data(new TileState[width * height])
{
    clear();
}
