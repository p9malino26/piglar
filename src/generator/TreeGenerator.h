#pragma once

#include <memory>
#include "../util/vectors.h"

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
        BoardPos generate();
        void writeTo(TileMap& roadMap, BoardPos startPos, bool flip);

        std::unique_ptr<TileMap> treeData;
        ~TreeGenerator();
    private:
        const TreeGenParams* params;
        std::unique_ptr<TreeGenData> lastGenData;
    };
}


