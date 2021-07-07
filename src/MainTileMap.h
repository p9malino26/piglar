#pragma once

#include "TileMap.h"
#include "util/singleton.h"


class MainTileMap : public TileMap
{
public:
    MainTileMap(int width, int height);
    SINGLETON(MainTileMap);
};

