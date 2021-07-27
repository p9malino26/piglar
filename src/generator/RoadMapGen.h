#pragma once

#include <memory>

class TileMap;

namespace Generator{ // todo get rid of namespace
    class TreeGenParams;
    void generateTerrain(TileMap&, const TreeGenParams& params);
}
