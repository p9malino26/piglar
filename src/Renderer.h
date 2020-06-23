#ifndef RENDERER_H 
#define RENDERER_H

#include "Scene.h"

class Renderer
{
public:
    Renderer(const Scene& _scene);

    void renderScene() const;
    void renderSprite() const;
private:
    const Scene* scene;
};

#endif
