#pragma once

#include <vector>
#include <utility>
#include <algorithm>
#include <stdexcept>

#include "vectors.h"
#include "util/CompassDirection.h"

//all rendering function deprecated

enum TileState {NO_ROAD=0, HORIZONTAL=1, VERTICAL, HOUSE, GREEN_SPACE};
inline bool isRoad(TileState state) {return state == HORIZONTAL || state == VERTICAL; }

class TileMap
{
public:
    //enum State {OFF, ON};

    TileMap(int width, int height);
    ~TileMap();
    
    inline int getWidth() const {return width;}
    inline int getHeight() const {return height;}
    inline BoardPos getSize() const {return {width, height};}

    inline bool isPositionOutside(const BoardPos& coord) const
    {
        return coord.x >= getWidth() || coord.y >= getHeight() ||
                coord.x < 0 || coord.y < 0;
    }
    
    inline void setTileState(const BoardPos& coord, TileState state)
    {
        data[getIndexFromCoord(coord)] = state;
    }

    inline TileState getTileState(const BoardPos& coord) const
    {
        return data[getIndexFromCoord(coord)];
    }

    inline TileState& getTile(const BoardPos& coord) {return data[getIndexFromCoord(coord)];}
    inline void clear() {std::memset(data, NO_ROAD, sizeof(TileState) * width * height);}

private:
	int width;
	int height;


    TileState* data;


    inline void ensurePositionIsInside(const BoardPos& coord) const
    {
        if(isPositionOutside(coord)) throw std::runtime_error("[ERROR] Attempt to access roadmap co-ordinate outside the range.");
    }

    inline int getIndexFromCoord(const BoardPos& coord) const
    {
        ensurePositionIsInside(coord);
        return width * coord.y + coord.x;
    }

};

