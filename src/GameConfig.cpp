//
// Created by patryk on 09/07/2021.
//

#include "GameConfig.h"

#include "TreeGenParams.h"
#include "MechanicsConfig.h"
#include "CameraConfig.h"

GameConfig::GameConfig() : generatorConfig(new TreeGenParams),
                                       mechanicsConfig(new MechanicsConfig),
                                       cameraConfig(new CameraConfig)
{}
