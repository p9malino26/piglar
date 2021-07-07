//
// Created by patryk on 06/07/2021.
//

#pragma once

#include "util/singleton.h"
#include "SquarePlayer.h"

#define PLAYER_SPEED 4.f


class Player: public SquarePlayer {
    //const float speed = 4.f;
public:

    explicit Player(const RealPos &startPos) : SquarePlayer(startPos, 0.7f)
    {
        instance = this;
    }

    float getSpeed() {return PLAYER_SPEED; }
    SINGLETON(Player)
};


