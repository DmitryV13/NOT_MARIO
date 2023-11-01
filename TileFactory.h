#pragma once
#include "Tile.h"
#include "random"
class coord;
class TileFactory {
public:
    Tile tile_map_inFactory[40][200];
    TileFactory();
private:
    sf::IntRect initRect_tile(char tile);
    void generation_map(char map[40][200]);
    coord* generationF1();
    coord* generationF2();
    coord* generationF3();
    coord* generationF4();
    coord* generate();
};

//#pragma once
//#include "Tile.h"
//#include "random"
//
//class TileFactory {
//private:
//
//sf::IntRect initRect_tile(char tile);
//void generation_map(std::string map[40][201]);
//void build_generation_map(std::string map[40][201]);
//
//
//public:
//    TileFactory();
//    Tile tile_map_inFactory[40][200];
//
//
//};