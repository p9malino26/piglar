#include "MainTileMap.h"

MainTileMap* MainTileMap::instance;

MainTileMap::MainTileMap(int width, int height) : TileMap(width, height)
{
instance = this;}
