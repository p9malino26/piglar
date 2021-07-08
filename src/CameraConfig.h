//
// Created by patryk on 07/07/2021.
//

#pragma once

#include "vectors.h"

struct CameraConfig
{
    float followSpeed;
    float moveSpeed;
    float zoomSpeed;

    std::pair<float, float> zoomRange;
};
