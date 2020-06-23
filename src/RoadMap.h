#ifndef ROADMAP_H
#define ROADMAP_H

/**
 * @todo write docs
 */

#include <vector>
#include <utility>

#include "GLMIncludes.h"
//#include "Entities.h"
#include "RoadMapGenCell.h"


//all rendering function deprecated

class RoadMap
{

public:
	RoadMap();
    
    inline int width() const {return WIDTH;}
    inline int height() const {return HEIGHT;}
    
    enum class TileColour {WHITE = 0, BLACK = 1};
	typedef TileColour RoadMapField;
    
    void updateGenNodes();
    
    inline RoadMapField& at(int x, int y)
    {
        int index = WIDTH * y + x;
        return m_data[index];        
    }
    
    inline RoadMapField& at(const glm::vec2i& coord)
    {
        int index = WIDTH * coord.y + coord.x;
        return m_data[index];        
    }
    
    inline void setWalkable(const glm::vec2i& coord)
    {
        at(coord) = TileColour::BLACK;
    }

    inline bool positionIsOutside(const glm::vec2i& coord)
    {
        return coord.x >= width() || coord.y >= height();
    }
    
    template<typename ... Args>
    void emplaceNode(Args&& ... args)
    {
        m_gen_nodes.emplace_back(this, std::forward<Args>(args) ...);
    }

    ~RoadMap();
	//void generateNewRoad(std::vector<House>& houses);
private:
    
	const int WIDTH = 20;
	const int HEIGHT = 20;
    
	RoadMapField* m_data;
    std::vector<RoadMapGenNode> m_gen_nodes;
    
};

#endif // ROADMAP_H
