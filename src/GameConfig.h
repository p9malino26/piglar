//
// Created by patryk on 07/07/2021.
//

#pragma once

#include <memory>

class TreeGenParams;
class MechanicsConfig;
class CameraConfig;

struct GameConfig
{
    std::unique_ptr<TreeGenParams> generatorConfig;
    std::unique_ptr<MechanicsConfig> mechanicsConfig;
    std::unique_ptr<CameraConfig> cameraConfig;

    GameConfig();
};