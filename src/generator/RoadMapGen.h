#pragma once

#include <memory>

class RoadMap;

namespace Generator {
    class BottomUpRectPlacer;

    class RoadMapGen
    {
    public:
        friend class SceneRenderer;
        RoadMapGen(RoadMap*);

        void generate();
        ~RoadMapGen();
    private:
        RoadMap* roadMap;
    };
}


