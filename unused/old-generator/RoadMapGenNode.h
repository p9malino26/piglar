#pragma once

#include "util/vectors.h"
#include "Util.h"
#include "Random.h"

//the road generation cellular automaton

class RoadMap;
class RoadMapGen;

class RoadMapGenNode
{
    RoadMap* m_roadmap;
    CompassDirection m_direction;
    glm::vec2i m_position;
    
    static const Fraction junction_prob;
    static const Fraction stop_or_turn_prob;
    
    static const int maxBlocksUntilJunction;
    static const int maxBlocksUntilTurnOrStop;
    
    bool m_stopped;
    
    int m_blocksAfterJunction;
    int m_blocksAfterCreationOrDirectionChange;
    
    void performAction();

    
    inline glm::vec2i left() const
    {
        return m_position + directionVec(compassDirFromRelative(m_direction, RelativeDirection::LEFT));
    }
    inline glm::vec2i right() const 
    {
        return m_position + directionVec(compassDirFromRelative(m_direction, RelativeDirection::RIGHT));
    }    
    inline glm::vec2i front() const
    {
        return m_position + directionVec(m_direction);
    }    
    inline glm::vec2i back() const
    {
        return m_position - directionVec(m_direction);
    }

    void setPosition(const glm::vec2i& newPos);
    void changePosition(const glm::vec2i& posDelta);


public:
    
    RoadMapGenNode (RoadMap* roadmap, CompassDirection direction, const glm::vec2i& position);
    void update();
    inline bool isStopped() const {return m_stopped;}
    inline void stop() {m_stopped = true;}

    /* on its way it can either:
    continue going straight in its direction
    change direction - only its direction attribute is modified
    branch out at a junction - this creates another node which travels in a direction perpendicular to said node
    stop - request deletion
    */


};
