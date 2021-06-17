#pragma once

#include <memory>

class RoadMap;

namespace Generator {
    class BottomUpRectPlacer;

    class RoadMapGen
    {
    public:
        RoadMapGen(RoadMap*);

        void generate();
        ~RoadMapGen();
    private:
        std::unique_ptr<BottomUpRectPlacer> rpr;
        RoadMap* roadMap;
    };
}


