#pragma once

#include <memory>

class TileMap;

namespace Generator {
    class BottomUpRectPlacer;

    class RoadMapGen
    {
    public:
        RoadMapGen(TileMap*);

        void generate();
        ~RoadMapGen();
    private:
        std::unique_ptr<BottomUpRectPlacer> rpr;
        TileMap* roadMap;
    };
}


