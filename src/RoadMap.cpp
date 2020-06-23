#include "RoadMap.h"
#include "Random.h"


RoadMap::RoadMap()
    :m_data(new RoadMapField[WIDTH * HEIGHT])
{
   /*for(int i = 0; i < WIDTH * HEIGHT; i++)
   {
       m_data[i] = TileColour(Random::randInt(0,1));
   }*/
   m_gen_nodes.reserve(10);
   glm::vec2i startingPos(Random::randInt(1, 4), Random::randInt(1, 4));
   emplaceNode( (Random::fiftyFifty() ? CompassDirection::NORTH : CompassDirection::SOUTH), startingPos);
   
   
}

void RoadMap::updateGenNodes()
{
    for(RoadMapGenNode node: m_gen_nodes) node.update();

}

RoadMap::~RoadMap()
{
    delete[] m_data;
}
