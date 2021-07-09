//
// Created by patryk on 08/07/2021.
//
#include "GameConfig.h"

#include <fstream>
#include <string>
#include <cassert>
#include <inipp/inipp.h>

#include "generator/TreeGenParams.h"
#include "MechanicsConfig.h"
#include "CameraConfig.h"

static std::map<std::string, std::string>* data;


#define stdConv(name, f, T) T name(const std::string& x) {return f(x);}
stdConv(toInt, std::stoi, int)
stdConv(toFloat, std::stof, float)

template <typename T>
static bool parse(T& dest, const std::string& key, T(*convFunc)(const std::string&))
{
    if (!data->contains(key)) {
        std::cerr << "Warning: label " << key << " not found!\n";
        return false;
    }

    dest = convFunc(data->at(key));
    return true;
}


static void parseMechanics(MechanicsConfig& config)
{

    parse(config.pigsCount, "pig_count", toInt);
    parse(config.tileMapSize, "tile_map_size", toInt);
    parse(config.playerSpeed, "player_speed", toFloat);
    parse(config.pigToPlayerSpeedRatio, "pig_player_speed_ratio", toFloat);
    parse(config.pigDetectionRange, "pig_detection_range", toFloat);

}

static void parseTerGen(Generator::TreeGenParams& config)
{
    parse(config.branchRoadLengthRange.first, "branch_len_min", toInt);
    parse(config.branchRoadLengthRange.second, "branch_len_max", toInt);

    parse(config.mainRoadLengthRange.first, "main_road_len_min", toInt);
    parse(config.mainRoadLengthRange.second, "main_road_len_max", toInt);

    parse(config.branchStepRange.first, "branch_step_min", toInt);
    parse(config.branchStepRange.second, "branch_step_max", toInt);

}

static void parseCamera(CameraConfig& config)
{
    parse(config.zoomRange.first, "zoom_min", toFloat);
    parse(config.zoomRange.second, "zoom_max", toFloat);
    parse(config.zoomSpeed, "zoom_speed", toFloat);
    parse(config.moveSpeed, "move_speed", toFloat);
    parse(config.initialZoom, "initial_zoom", toFloat);
}

void loadConfigFromFile(GameConfig& config, const std::string& fName)
{
    std::ifstream is(fName);
    assert(is.is_open());
    inipp::Ini<char> ini;
    ini.parse(is);

    data = &ini.sections["Mechanics"];
    parseMechanics(*config.mechanicsConfig);

    data = &ini.sections["TerrainGen"];
    parseTerGen(*config.generatorConfig);

    data = &ini.sections["Camera"];
    parseCamera(*config.cameraConfig);

}
