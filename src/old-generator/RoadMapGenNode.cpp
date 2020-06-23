#include "RoadMapGenCell.h"

#include "RoadMap.h"
#include "Random.h"
#include "Util.h"

#include <stdexcept>

const Fraction RoadMapGenNode::junction_prob {1, maxBlocksUntilJunction};
const Fraction RoadMapGenNode::stop_or_turn_prob{1, maxBlocksUntilTurnOrStop};

const int RoadMapGenNode::maxBlocksUntilJunction = 5;
const int RoadMapGenNode::maxBlocksUntilTurnOrStop = 8;


bool somethingShouldBeDone(int blocksAfterThing, int maxBlocksUntilThing, const Fraction& probabilityFraction);

RoadMapGenNode::RoadMapGenNode (RoadMap* roadmap, CompassDirection direction, const glm::vec2i& position)
:m_roadmap(roadmap), m_direction(direction), m_position(position)
{
    
}

void RoadMapGenNode::update()
{
    m_roadmap->setWalkable(m_position);
    performAction();
    if (!isStopped())
    {
        if (m_roadmap->positionIsOutside(m_position + directionVec(m_direction)))
        {
            stop();
        }
    }
}

void RoadMapGenNode::performAction()
{
    if( somethingShouldBeDone(m_blocksAfterJunction, maxBlocksUntilJunction, junction_prob))// if a junction must be created
    {
        //decide whether the junction is double or not
        if(Random::fiftyFifty())//junction is double
        {
            //construct new nodes for the junction
            m_roadmap->emplaceNode(compassDirFromRelative(m_direction, RelativeDirection::LEFT), left());
            m_roadmap->emplaceNode(compassDirFromRelative(m_direction, RelativeDirection::RIGHT), right());

            m_blocksAfterJunction = 0;
            return;
        }
    }else
    {
        m_blocksAfterJunction++;
    }

    if( somethingShouldBeDone(m_blocksAfterCreationOrDirectionChange, maxBlocksUntilTurnOrStop, stop_or_turn_prob) ) // see if we should stop or turn
    {
        if(Random::fractionChance(Fraction(1, 3))) // if we are turning
        {
            //choose the direction randomly
            m_direction = compassDirFromRelative(m_direction, (Random::fiftyFifty() ? RelativeDirection::LEFT : RelativeDirection::RIGHT));
            

        }else
        {
            //otherwise, we are stopping
            m_stopped = true;
        }
        
        m_blocksAfterCreationOrDirectionChange = 0;
    }else
    {
        m_blocksAfterCreationOrDirectionChange++;
        return;
    }
    
}


void RoadMapGenNode::setPosition(const glm::vec2i& newPos)
{
    if (m_roadmap->positionIsOutside(newPos))
        throw std::runtime_error("[CRASH ERROR] Attempt to set position outside of the roadmap");
    
    m_position = newPos;
}

void RoadMapGenNode::changePosition(const glm::vec2i& posDelta)
{
    setPosition(m_position + posDelta);
}

bool somethingShouldBeDone(int blocksAfterThing, int maxBlocksUntilThing, const Fraction& probabilityFraction)
{
    return (blocksAfterThing == maxBlocksUntilThing || Random::fractionChance(probabilityFraction)) &&  blocksAfterThing != 1;
}