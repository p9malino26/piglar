#pragma once
#include <vector>
#include "util/vectors.h"
#include "util/CachedFunction.h"

class Scene;
class TileMap;

class SceneRenderer
{
    const Scene& scene;
    CachedFunction<int, glm::vec3> getHouseColor;
    const TileMap& tileMap;
public:
    explicit SceneRenderer(const Scene& scene);
    ~SceneRenderer();

    /**
     * renders the scene
     */
    void render ();
    void drawTileMap();


};
