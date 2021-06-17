#pragma once

/**
 * @todo write docs
 */

#include <vector>
#include <utility>
#include <algorithm>
#include <stdexcept>

#include "GLMIncludes.h"
#include "util/CompassDirection.h"

//all rendering function deprecated

typedef bool CellType;

class RoadMap
{
public:
    //enum State {OFF, ON};


	RoadMap(int width, int height);
    inline ~RoadMap() {delete[] data;}
    
    inline int getWidth() const {return width;}
    inline int getHeight() const {return height;}
    inline glm::vec2i getSize() const {return {width, height};}

    inline bool isPositionOutside(const glm::vec2i& coord) const
    {
        return coord.x >= getWidth() || coord.y >= getHeight();
    }
    
    inline void setFieldState(const glm::vec2i& coord, CellType state)
    {
        data[getIndexFromCoord(coord)] = state;
    }

    inline void toggleFieldState(const glm::vec2i& coord)
    {
        CellType celldata = data[getIndexFromCoord(coord)];
        data[getIndexFromCoord(coord)] = !celldata;
    }

    inline CellType getFieldState(const glm::vec2i& coord) const
    {
        return data[getIndexFromCoord(coord)];
    }

    void setLine(const glm::vec2i& startPos, CompassDirection direction, int length, CellType state);

    inline void clear() {std::memset(data, 0, width * height);}


private:
	int width;
	int height;


    CellType* data;


    inline void ensurePositionIsInside(const glm::vec2i& coord) const
    {
        if(isPositionOutside(coord)) throw std::runtime_error("[ERROR] Attempt to access roadmap co-ordinate outside the range.");
    }

    inline int getIndexFromCoord(const glm::vec2i& coord) const
    {
        ensurePositionIsInside(coord);
        return width * coord.y + coord.x;
    }

    /*inline State& at(const glm::vec2i& coord)
    {
        ensurePositionIsInside(coord);
        int index = width * coord.y + coord.x;
        return data[index];
    }*/

    //fuck this constness; let's copy and paste this code!
    /*inline const bool& at(const glm::vec2i& coord) const
    {
        ensurePositionIsInside(coord);
        int index = width * coord.y + coord.x;
        return data.at(index);        
    }*/
    
    
};

