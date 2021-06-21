//
// Created by patryk on 21/06/2021.
//
#include "RoadMap.h"
#include "Entity.h"
#include "util/compassVec.h"

float dummy;

float fractionalPart(float f)
{
    return std::modf(f, &dummy);
}

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

void moveCDVertical(const RoadMap& roadMap, Entity& entity, float distance)
{
    auto isOnRoad = [&roadMap] (const RealPos& pos) -> bool
    {
        BoardPos intpos{std::floor(pos.x), std::floor(pos.y)};
        if (roadMap.isPositionOutside(intpos)) return false;
        return roadMap.getFieldState(intpos);
    };
    auto newPos = entity.getPos();
    newPos.y += distance;

    RealPos vertices[] = {{0.f,0.f}, {1.f, 0.f}, {0.f, 1.f}, {1.f, 1.f}};


    for (auto& vertex: vertices)
    {
        vertex *= RealPos {entity.getWidth(), entity.getHeight()};
        vertex += newPos;

        if (!isOnRoad(vertex))
        {
            auto frac = fractionalPart(vertex.y);
            newPos.y += distance < 0 ? 1- frac : -frac;
            break;
        }
    }

    entity.setPos(newPos);

}

void moveEntityWithCollisionDetection(const RoadMap& roadMap, Entity& entity, const RealPos& posDelta)
{
    auto newPos = entity.getPos() + posDelta;
    if (isLegalPosition(roadMap, entity, entity.getPos()) && !isLegalPosition(roadMap, entity, newPos))
        return;

    entity.setPos(newPos);
}