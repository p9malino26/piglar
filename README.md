# The Pig Game
# Background
This is my first major programming project in C++, which I've done to exercise my programming skills for games. This is also my first go at random terrain generation.

The objective of the game is to round up all the pigs and take them to the truck in the shortest amount of time. When you are close enough to a pig, it will follow you. Initially, the pigs are scattered randomly across the board.

When all the pigs are taken to the truck, the game is completed.

# Build

You will need the following dependencies:
* glfw (3.3) <https://www.glfw.org/>
* freetype (I used 2.10, but I think you can get away with any as long as it's freetype2!) <https://www.freetype.org/>
* glm (0.9.9) <https://glm.g-truc.net/0.9.9/index.html>

For example, on Arch Linux, they will need to be installed by
`# pacman -S glfw freetyp2 glm`

## Compilation
* Ensure your working directory is the directory containing CMakeLists.txt
* To build, run cmake:
`$ cmake .`
* Then compile:
`$ make`

You should then have the executable file in your working directory, which you can execute.

# Running

##Command line arguments
* --seed : A seed for the level
* --config: path to the config file

## Execution

For example, on Linux:
`./piglar --seed 7 --config config.txt`

# Gameplay
## Controls

* Move player: w/a/s/d
* Close window: ESC

* Toggle cheat mode: c (only when cheats is set to 1 in the config file)
* Change zoom (cheat mode only): mouse scroll
* Move camera  (cheat mode only): mouse drag or up/down/left/right keys
* Teleport player to cursor (cheat mode only): K
* Teleport all pigs to player (cheat mode only): T

## Configuration

The file config.txt contains various customizable options for various parts of the game, which you can fiddle with. For example, you can increase the difficulty of the game by decreasing the pig speed!
Each option is described in the file.

# Credits
* The directory src/vendor contains dependencies that I do not own. These are:
  * glad (as OpenGL loader) <https://github.com/dav1dde/glad-web>
  * GLFont (for text rendering) <https://github.com/jtberglund/GLFont>
  * inipp (for config file parsing) <https://github.com/mcmtroffaes/inipp>
  * stb_image (for texture loading) <https://github.com/nothings/stb/blob/master/stb_image.h>
  
* The classes for OpenGL in src/opengl/ were inspired by the OpenGL tutorials by TheChernoProject:
  <https://www.youtube.com/user/TheChernoProject>
