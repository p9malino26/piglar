#include "TileMap.h"

TileMap::TileMap(int width, int height)
    :width(width), height(height), data(new TileState[width * height])
{
    clear();
}

TileMap::~TileMap() {
    delete[] data;
}
