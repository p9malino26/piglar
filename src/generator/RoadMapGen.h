#pragma once

#include <memory>

class TileMap;

namespace Generator{
    class TreeGenParams;
    void generateTerrain(TileMap&, const TreeGenParams& params);
}
