#pragma once
#include "Tile.h"
#include "random"
class coord;
class TileFactory {
public:
    Tile tile_map_inFactory[40][200];
    TileFactory(int n, int m);

    const int n;
    const int m;
private:
    sf::IntRect initRect_tile(char tile);
    void generation_map(vector<vector<char>>& map);

    void generate_solid_surface(vector<int>& x, vector<int>& y, vector<vector<char>>& map);
    coord* generate_landscape();
    coord* generationF1();
    coord* generationF2();
    coord* generationF3();
    coord* generationF4();
    
    std::vector<std::pair<int, int>>  lakes_generation(vector<int>& x, vector<int>& y, vector<vector<char>>& map);
    void fill_lakes(vector<int>& x, vector<int>& y, vector<pair<int, int>> coords_for_water, vector<vector<char>>& map);
    void fill_lake(int& water_level, int pos_x, int pos_y, vector<vector<char>>& map);

    void tunnels_generation(vector<int>& y, vector<vector<char>>& map);
    void one_tunnel_generation(int pos_x, int pos_y, int height, vector<vector<char>>& map);
    void left_zigzag(int pos_x, int pos_y, vector<vector<char>>& map);
    void right_zigzag(int pos_x, int pos_y, vector<vector<char>>& map);
    void upward(int pos_x, int pos_y, vector<vector<char>>& map);

    void generate_platforms(vector<int>& x, vector<int>& y, vector<vector<char>>& map);
    void generate_platform(int pos_x, int pos_y, int width, int height, vector<vector<char>>& map);
    void platform_filter_y(int pos_x, int pos_y, vector<int>& y, int width, int height, vector<vector<char>>& map);

    void texture_arrangement(vector<vector<char>>& map);
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