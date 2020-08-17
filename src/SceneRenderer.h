#pragma once

class Scene;
class Renderer;


class SceneRenderer
{
    const Scene* scene;
public:
    explicit SceneRenderer(const Scene* scene);

    /**
     * renders the scene
     */
    void render () const;
};

