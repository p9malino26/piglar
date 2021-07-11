#pragma once
#include <vector>
#include "TexId.h"

class Scene;
class Renderer;

class PosRectangle;
class SceneRenderer
{
    const Scene* scene;
public:
    explicit SceneRenderer(const Scene* scene);
    ~SceneRenderer();

    /**
     * renders the scene
     */
    void render ();

};
