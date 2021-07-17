#pragma once

/**
 * @todo write docs
 */

#include <vector>
#include <utility>
#include <algorithm>
#include <stdexcept>

#include "vectors.h"
#include "util/CompassDirection.h"

//all rendering function deprecated

enum TileState {NO_ROAD=0, HORIZONTAL=1, VERTICAL=2};

class TileMap
{
public:
    //enum State {OFF, ON};


    TileMap(int width, int height);
    inline ~TileMap() {delete[] data;}
    
    inline int getWidth() const {return width;}
    inline int getHeight() const {return height;}
    inline glm::vec2i getSize() const {return {width, height};}

    inline bool isPositionOutside(const glm::vec2i& coord) const
    {
        return coord.x >= getWidth() || coord.y >= getHeight() ||
                coord.x < 0 || coord.y < 0;
    }
    
    inline void setTileState(const glm::vec2i& coord, TileState state)
    {
        data[getIndexFromCoord(coord)] = state;
    }

    inline TileState getTileState(const glm::vec2i& coord) const //TODO rename to boardpos
    {
        return data[getIndexFromCoord(coord)];
    }

    inline void clear() {std::memset(data, NO_ROAD, sizeof(TileState) * width * height);}

private:
	int width;
	int height;


    TileState* data;


    inline void ensurePositionIsInside(const glm::vec2i& coord) const
    {
        if(isPositionOutside(coord)) throw std::runtime_error("[ERROR] Attempt to access roadmap co-ordinate outside the range.");
    }

    inline int getIndexFromCoord(const glm::vec2i& coord) const
    {
        ensurePositionIsInside(coord);
        return width * coord.y + coord.x;
    }

    
    
};

