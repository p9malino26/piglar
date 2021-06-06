#pragma once

#include <memory>

class RoadMap;
namespace Generator { class RectanglePlacementRecorder;}

class RoadMapGen
{
public:
    friend class SceneRenderer;
    RoadMapGen(RoadMap*);

    void generate();
    ~RoadMapGen();
private:
    RoadMap* roadMap;
    std::unique_ptr<Generator::RectanglePlacementRecorder> rpr;
};
