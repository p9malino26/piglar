#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <map>
#include <utility>

#include "opengl/Shader.h"
#include "opengl/VertexArray.h"
#include "opengl/Buffer.h"
#include "opengl/Texture.h"

class ResourceManager
{
public:
    template <typename T>
    using Container = std::map<std::string, T>;
private:
    static Container<Shader> shaders;
    static Container<Buffer> buffers;
    static Container<VertexArray> vertexArrays;

    static Container<Texture> textures;
    //static std::map<std::string, Shape> 
    //static Shape basicSquare;
    //static std::map<std::string, Texture> textures;
    //static std::map<std::string, Shape> shapeBuffers;

    template <typename MapType, typename ... Args>
    static void construct(MapType map, const std::string& objectName, Args&& ... args)
    {
        map.emplace(std::piecewise_construct, std::forward_as_tuple(objectName), std::forward_as_tuple(args ...));
    }
public:
    template <typename ... Args>
    static void createShader(const std::string& shaderName, Args&& ... args)
    {
        construct(shaders, shaderName, args ...);
    }

    static Shader* getShader(const std::string& name)
    {
        return &(shaders[name]);
    }

    static void createVertexArray(const std::string& vaoName)
    {
        construct(vertexArrays, vaoName);
    }

    static VertexArray* getVertexArray(const std::string& name)
    {
        return &(vertexArrays[name]);
    }

    template <typename ... Args>
    static void createBuffer(const std::string& name, Args&& ... args)
    {
        construct(buffers, name, args ...);
    }

    static Buffer* getBuffer(const std::string& name)
    {
        return &(buffers[name]);
    }
    
    template <typename ... Args>
    static void createTexture(const std::string& name, Args&& ... args)
    {
        construct(textures, name, args ...);
    }

    static Texture* getTexture(const std::string& name)
    {
        return &(textures[name]);
    }
};

#endif
