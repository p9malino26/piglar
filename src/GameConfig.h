//
// Created by patryk on 07/07/2021.
//

#pragma once

#include <memory>

namespace Generator {class TreeGenParams; };
class MechanicsConfig;
class CameraConfig;

struct GameConfig
{
    std::unique_ptr<Generator::TreeGenParams> generatorConfig;
    std::unique_ptr<MechanicsConfig> mechanicsConfig;
    std::unique_ptr<CameraConfig> cameraConfig;

    GameConfig();
};