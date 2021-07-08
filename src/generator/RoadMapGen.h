#pragma once

#include <memory>

class TileMap;

namespace Generator {
    class TreeGenerator;
    class BottomUpRectPlacer;
    class TreeGenParams;

    class RoadMapGen
    {
    public:
        RoadMapGen(TileMap*, const TreeGenParams& params);

        void generate();
        ~RoadMapGen();
    private:
        std::unique_ptr<BottomUpRectPlacer> rpr;
        std::unique_ptr<TreeGenerator> treeGen;
        TileMap* roadMap;
    };
}


