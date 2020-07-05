#pragma once

/**
 * @todo write docs
 */

#include <vector>
#include <utility>
#include <stdexcept>

#include "GLMIncludes.h"

//all rendering function deprecated

class RoadMap
{
public:
    //enum State {OFF, ON};


	RoadMap(int width, int height);
    
    inline int getWidth() const {return width;}
    inline int getHeight() const {return height;}
    

    inline bool isPositionOutside(const glm::vec2i& coord) const
    {
        return coord.x >= getWidth() || coord.y >= getHeight();
    }
    
    inline void setFieldState(const glm::vec2i& coord, bool state)
    {
        data[getIndexFromCoord(coord)] = state;
    }

    inline void toggleFieldState(const glm::vec2i& coord)
    {
        bool celldata = data[getIndexFromCoord(coord)];
        data[getIndexFromCoord(coord)] = !celldata;
    }

    inline bool getFieldState(const glm::vec2i& coord) const
    {
        return data[getIndexFromCoord(coord)];
    }

    void setLine(const glm::vec2i& startPos, )


private:

	int width;
	int height;


    std::vector<bool> data;


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

