//
// Created by patryk on 21/06/2021.
//

#include "Entity.h"

#pragma once
class TileMap;

RealPos getCollisionResolutionDelta(const TileMap& tileMap, Entity& entity, const RealPos& initialDelta);

class SquarePlayer: public Entity{
    float m_sideLength;
public:
    SquarePlayer(const RealPos& startPos, float sideLength): Entity(startPos), m_sideLength(sideLength) {}

    float getWidth() override;
    float getHeight() override;
};
