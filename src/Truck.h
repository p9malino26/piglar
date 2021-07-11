//
// Created by patryk on 09/07/2021.
//

#pragma once

#include "Entity.h"

class Truck : public Entity{
public:

    float getWidth() const override { return 2.3f;}
    float getHeight() const override { return 0.9f; }
};


