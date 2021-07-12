#include <ctime>

#include "Game.h"
#include "GameConfig.h"

#include "generator/TreeGenParams.h"
#include "MechanicsConfig.h"
#include "CameraConfig.h"

void loadConfigFromFile(GameConfig& config, const std::string& fName);

int main(int argc, char* argv[])
{
    GameConfig config;

    int arg = 0;
    unsigned int seed = 0;

    bool isConfig = 0;

    for(;arg < argc;++arg)
    {
        if (!strcmp(argv[arg], "--config")) {
            loadConfigFromFile(config,argv[++arg]);
            std::cout << "[INFO] Loading from config file " << argv[arg] << std::endl;
            isConfig = true;
        }
        else if (!strcmp(argv[arg], "--seed"))
        {
            seed = std::stoi(argv[++arg]);
        }
    }

    if (!isConfig)
    {
        std::cout << "[INFO] No config file provided, using default settings." << std::endl;
    }

    if (!seed)
    {
        seed = time(nullptr);
        std::cout << "[INFO] No seed provided or seed of zero given, using random seed of: " << seed << std::endl;
    }

    Game game(config, seed);
    game.runMainLoop();
}