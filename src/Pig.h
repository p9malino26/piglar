//
// Created by patryk on 06/07/2021.
//

#pragma once

#include "SquarePlayer.h"

class Player;

class Pig : public SquarePlayer{
    float m_minPlayerDistance;

    static float speed;
    static float detectionRange;
public:
    Pig(const RealPos& startPos);

    void update();

    static void init(float playerSpeedRatio, float detectionRange);
};


