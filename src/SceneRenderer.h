#pragma once
#include <vector>

class Scene;

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
