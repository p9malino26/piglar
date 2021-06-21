#pragma once

#include <vector>

#include "RoadMapGenNode.h"

class RoadMap;

class RoadMapGen
{
    RoadMap* m_roadMap;

    std::vector<RoadMapGenNode> m_gen_nodes;
public:
    RoadMapGen(RoadMap* RoadMap);
    void performOneIteration();
    
    template<typename ... Args>
    void emplaceNode(Args&& ... args)
    {
        m_gen_nodes.emplace_back(this, std::forward<Args>(args) ...);
    }
};