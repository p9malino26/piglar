//
// Created by patryk on 21/06/2021.
//

#include "Entity.h"

#pragma once

class SquarePlayer: public Entity{
    float m_sideLength;
public:
    SquarePlayer(const RealPos& startPos): Entity(startPos), m_sideLength(0.7f) {}
    float getWidth() override;

    float getHeight() override;
};


