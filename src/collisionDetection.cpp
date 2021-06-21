//
// Created by patryk on 21/06/2021.
//
#include "RoadMap.h"
#include "Entity.h"
#include "util/compassVec.h"

namespace {
    bool isLegalPosition(const RoadMap &roadMap, Entity &entity, const RealPos &entityPos)
    {
        auto isOnRoad = [&roadMap] (const RealPos& pos) -> bool
        {
            BoardPos intpos{std::floor(pos.x), std::floor(pos.y)};
            if (roadMap.isPositionOutside(intpos)) return false;
            return roadMap.getFieldState(intpos);
        };

        return isOnRoad(entityPos) &&
            isOnRoad(entityPos + (static_cast<RealPos>(EAST_VEC) * entity.getWidth())) &&
            isOnRoad(entityPos + (static_cast<RealPos>(NORTH_VEC) * entity.getHeight())) &&
            isOnRoad(entityPos + static_cast<RealPos>(EAST_VEC + NORTH_VEC) * RealPos(entity.getWidth(), entity.getHeight()));
    }
}

void moveEntityWithCollisionDetection(const RoadMap& roadMap, Entity& entity, const RealPos& posDelta)
{
    auto newPos = entity.getPos() + posDelta;
    if (isLegalPosition(roadMap, entity, entity.getPos()) && !isLegalPosition(roadMap, entity, newPos))
        return;

    entity.setPos(newPos);
}