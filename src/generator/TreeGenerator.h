#pragma once

#include <memory>

#include "../GLMIncludes.h"
class TileMap;

namespace Generator {
    class TreeGenParams;
    class TreeGenData;

    class TreeGenerator
    {
    public:

        //methods
        TreeGenerator(const TreeGenParams& params);
        /**
         * Prepares a tree inside. Returns the rectangular width and height of the tree
         */
        glm::vec2i generate();
        void writeTo(TileMap& roadMap, glm::vec2i startPos, bool flip);

        std::unique_ptr<TileMap> treeData;
        ~TreeGenerator();
    private:
        const TreeGenParams* params;
        std::unique_ptr<TreeGenData> lastGenData;
    };
}


