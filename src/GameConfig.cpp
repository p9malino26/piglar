//
// Created by patryk on 09/07/2021.
//

#include "GameConfig.h"

#include "generator/TreeGenParams.h"
#include "MechanicsConfig.h"
#include "CameraConfig.h"

GameConfig::GameConfig() : generatorConfig(new Generator::TreeGenParams),
                                       mechanicsConfig(new MechanicsConfig),
                                       cameraConfig(new CameraConfig)
{}
