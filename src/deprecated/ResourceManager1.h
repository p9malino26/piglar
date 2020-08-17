#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <memory>

#include "opengl/Shader.h"
#include "opengl/VertexArray.h"
#include "opengl/Buffer.h"
#include "opengl/Texture.h"

class ResourceManager
{
public:
    ResourceManager();
    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<Buffer     > vbo;
    std::unique_ptr<Buffer     > ebo;
    std::unique_ptr<Shader     > shader;
};

#endif
