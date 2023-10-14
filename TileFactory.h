#pragma once
#include "Tile.h"

class TileFactory {
private:



sf::IntRect initRect_tile(char tile);

public:
    TileFactory();
    Tile tile_map_inFactory[20][100];


};

