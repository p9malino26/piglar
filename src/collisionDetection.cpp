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
#define _BV(x) (1 << x)
void moveComponent(const RoadMap& roadMap, Entity& entity, float distance, bool vertical)
{
    auto isOnRoad = [&roadMap] (const RealPos& pos) -> bool
    {
        BoardPos intpos{std::floor(pos.x), std::floor(pos.y)};
        if (roadMap.isPositionOutside(intpos)) return false;
        return roadMap.getFieldState(intpos);
    };

    auto component = [vertical] ( RealPos& pos) -> float& {return vertical ? pos.y : pos.x; };
    auto newPos = entity.getPos();
    component(newPos) += distance;

    RealPos vertices[4] = {{0.f,0.f}, {1.f, 0.f}, {0.f, 1.f}, {1.f, 1.f}};
    bool illegal[4] {0,0,0,0};
    int illegalCount = 0;
    int lastIllegalVertexIndex;

    for (int i = 3; i >= 0; --i) {
        auto& vertex = vertices[i];
        vertex *= RealPos {entity.getWidth(), entity.getHeight()};
        vertex += newPos;

        if (!isOnRoad(vertex))
        {
            illegal[i] = true;
            lastIllegalVertexIndex = i;
            ++illegalCount;
        }
    }

    //if (illegalCount == 0 || illegalCount == 4) return;

    bool shouldCorrect = illegalCount != 0 && (illegalCount != 2 ||
            (illegalCount == 2 && (vertical && (illegal[0] && illegal[1] || illegal[2] && illegal[3]) || !vertical && (illegal[0] && illegal[2] || illegal[1] && illegal[3]))));

    if (shouldCorrect)
    {
        auto frac = fractionalPart(component(vertices[lastIllegalVertexIndex]) + 1.f);
        component(newPos) += distance < 0 ? 1- frac : -frac ;
        //component(newPos) += distance < 0 ? 1- frac + 0.01 : -(frac + 0.01);
    }
    //std::for_each(vertices, vertices + 4, [&isOnRoad] (auto& v) {assert(isOnRoad(v));});

    entity.setPos(newPos);

}

void moveEntityWithCollisionDetection(const RoadMap& roadMap, Entity& entity, const RealPos& posDelta)
{
    moveComponent(roadMap, entity, posDelta.x, false);
    moveComponent(roadMap, entity, posDelta.y, true);
}

//old moveComponent
/*
 *     auto isOnRoad = [&roadMap] (const RealPos& pos) -> bool
    {
        BoardPos intpos{std::floor(pos.x), std::floor(pos.y)};
        if (roadMap.isPositionOutside(intpos)) return false;
        return roadMap.getFieldState(intpos);
    };

    auto component = [vertical] ( RealPos& pos) -> float& {return vertical ? pos.y : pos.x; };
    auto newPos = entity.getPos();
    component(newPos) += distance;

    RealPos vertices[] = {{0.f,0.f}, {1.f, 0.f}, {0.f, 1.f}, {1.f, 1.f}};
    bool illegal[4] {0,0,0,0};
    int illegalList = 0;
    int illegalCount = 0;


    for (int i = 3; i >= 0; --i) {
        auto& vertex = vertices[i];
        vertex *= RealPos {entity.getWidth(), entity.getHeight()};
        vertex += newPos;

        if (!isOnRoad(vertex))
        {
            illegal[i] = true;
            illegalList |= _BV(illegalCount++);
        }
    }

    if (illegalCount == 0) return;

    enum Orientation {NONE, HORIZONTAL, VERTICAL};

    Orientation illegalOrientation;

    if (illegalList == (_BV(2) | _BV(3)) || illegalList == (_BV(0) | _BV(1)))
        illegalOrientation = HORIZONTAL;
    else if (illegalList == (_BV(0) | _BV(2)) || illegalList == (_BV(1) | _BV(3)))
        illegalOrientation = VERTICAL;
    else
        illegalOrientation = NONE;


    for (int i = 3; i >= 0; --i)
    {
        auto& vertex = vertices[i];
        if (illegal[i]) {
            if (illegalOrientation == NONE || (illegalOrientation == HORIZONTAL) && vertical || (illegalOrientation == VERTICAL) && !vertical)
            {
                auto frac = fractionalPart(component(vertex));
                component(newPos) += distance < 0 ? 1- frac : -frac;
                break;
            }


        }
    }

    entity.setPos(newPos);
 */