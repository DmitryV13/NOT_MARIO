#pragma once
#include "Tile.h"
#include "random"

class TileFactory {
private:

    sf::IntRect initRect_tile(char tile);
    void generation_map(std::string map[40][201]);

public:
    TileFactory();
    //std::string template_2[40];
    Tile tile_map_inFactory[40][200];


};

