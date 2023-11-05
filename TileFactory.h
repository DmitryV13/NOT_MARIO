#pragma once
#include "Tile.h"
#include "random"

class TileFactory {
private:

sf::IntRect initRect_tile(char tile);
void generation_map(std::string map[40][201]);
void build_generation_map(std::string map[40][201]);

public:
    TileFactory();
    Tile tile_map_inFactory[40][200];


};

