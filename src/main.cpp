#include "Game.h"
#include "GameConfig.h"

#include "generator/TreeGenParams.h"
#include "MechanicsConfig.h"
#include "CameraConfig.h"

void loadConfigFromFile(GameConfig& config, const std::string& fName);

int main(int argc, char* argv[])
{
    GameConfig config;
    if (argc > 1) {
        std::cout << "[INFO] Loading from config file " << argv[1] << std::endl;
        loadConfigFromFile(config,argv[1]);
    } else {
        std::cout << "[INFO] No config file provided, using default settings." << std::endl;

    }
    Game game(config);
    game.runMainLoop();
}