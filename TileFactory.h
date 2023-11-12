#pragma once
#include "Tile.h"
#include "random"
class coord;
class TileFactory {
public:
    Tile tile_map_inFactory[40][200];
    TileFactory();

    static const int n = 40;
    static const int m = 200;
private:
    sf::IntRect initRect_tile(char tile);
    void generation_map(char map[40][200]);

    void generate_solid_surface(int x[200], int y[200], char map[40][200]);
    coord* generate_landscape();
    coord* generationF1();
    coord* generationF2();
    coord* generationF3();
    coord* generationF4();
    
    std::vector<std::pair<int, int>>  lakes_generation(int x[200], int y[200], char map[40][200]);
    void fill_lakes(int x[200], int y[200], vector<pair<int, int>> coords_for_water, char map[40][200]);
    void fill_lake(int& water_level, int pos_x, int pos_y, char map[40][200]);

    void tunnels_generation(int y[200], char map[40][200]);
    void one_tunnel_generation(int pos_x, int pos_y, int height, char map[40][200]);
    void left_zigzag(int pos_x, int pos_y, char map[40][200]);
    void right_zigzag(int pos_x, int pos_y, char map[40][200]);
    void upward(int pos_x, int pos_y, char map[40][200]);

    void generate_platforms(int x[200], int y[200], char map[40][200]);
    void generate_platform(int pos_x, int pos_y, int width, int height, char map[40][200]);
    void platform_filter_y(int pos_x, int pos_y, int y[200], int width, int height, char map[40][200]);
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