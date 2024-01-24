#pragma once
#include <random>
#include "Tile.h"
#include "random"
class coord;

class TileFactory {
private:

    float template_W;//n
    float template_H;//m
    short int type_template;
    short int level;
    std::vector<std::vector<char>> generation_template;

    //Max
    void generation_map_Boev(vector<vector<char>>& map);


    //Dimon
    void generation_map_Voicu(std::vector<std::vector<char>>& map);
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


    //Richard
    void map_generation(vector<vector<char>>&);
    bool getPosPlayer(int, int);
    void flatland(vector<vector<char>>&, int& i, int& j, int shift, std::mt19937 gen);
    void mountainous_terrain(vector<vector<char>>&, int& i, int& j, int& shift, std::mt19937 gen);
    void water_bodies(vector<vector<char>>&, int& i, int& j, int shift, std::mt19937 gen);
    void tunnel(vector<vector<char>>&, int& i, int& j, int shift, std::mt19937 gen);
    void wormhole(vector<vector<char>>&, int& i, int& j, int shift, std::mt19937 gen);
    void cavern(vector<vector<char>>&, int& i, int& j, int shift, std::mt19937 gen);
    void start_of_map_generation_(vector<vector<char>>&, int& i, int& j, std::mt19937 gen);
    void filter_map(vector<vector<char>>&);
    int count_empty_neighbors(vector<vector<char>>&, int i, int j);
    void filter_map1(vector<vector<char>>&);
    bool has_blocks_on_both_sides(vector<vector<char>>&, int i, int j);
    void artist_method(vector<vector<char>>&);
    void fill_lakes_with_ground(vector<vector<char>>&);

public:

    TileFactory(float temp_W, float temp_H, short int level);
    char give_generation_letter(int i, int j);
};