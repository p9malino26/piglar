//
// Created by patryk on 07/07/2021.
//

#pragma once

#include "vectors.h"

struct CameraConfig
{
    float followSpeed = 0.2f;
    float moveSpeed = 4.2f;
    float zoomSpeed = 5.0f;
    float initialZoom = 0.1f;
    std::pair<float, float> zoomRange = {0.01f, 0.8f};
};
