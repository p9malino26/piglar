//
// Created by patryk on 21/06/2021.
//

#include "Entity.h"

#pragma once

class SquarePlayer: public Entity{
    float m_sideLength;
public:
    SquarePlayer(): Entity({0.f,0.f}), m_sideLength(0.7f) {}
    float getWidth() override;

    float getHeight() override;
};


