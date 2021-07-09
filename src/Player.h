//
// Created by patryk on 06/07/2021.
//

#pragma once

#include "util/singleton.h"
#include "SquareEntity.h"


class Player: public SquareEntity {
    float speed;
public:

    explicit Player(float speed) : SquareEntity(RealPos(0), 0.7f), speed(speed) {
        instance = this;
    }

    float getSpeed() {return speed; }
    SINGLETON(Player)
};


