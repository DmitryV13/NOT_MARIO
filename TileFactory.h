#pragma once
#include "Tile.h"
#include "random"

#include "random"
class coord;
class TileFactory {
public:
    Tile tile_map_inFactory[40][200];
    TileFactory(int n, int m);

    float template_W;
    float template_H;
    void generation_map(std::vector<std::vector<char>>& map);
    
public:
    
    TileFactory(float temp_W, float temp_H);
    std::vector<std::vector<char>> generation_template;
    std::string a[35] = {
    const int n;
    const int m;
private:
    sf::IntRect initRect_tile(char tile);
    void generation_map(vector<vector<char>>& map);

    "                                                                                                    ",
    "                                                                                                    ",
    "                                                                                                    ",
    "                                                                                                    ",
    "                                                                                                    ",
    "                                                                                                    ",
    "                                                                                                    ",
    "                                                                                                    ",
    "                                                                                                    ",
    "                                                                                                    ",
    "                                                                                                    ",
    "                                                                                                  3 ",
    "                                                                                                    ",
    "                                                                                                    ",
    "                                                                                                 <  ",
    "                                                                                    2      LAAP  LAA",
    "                                                                                           CBBD  CBB",
    "                                                           AAAAAAAAAAAAAAAAAAAAAAAP        CBBD  CBB",
    "                                                           BBBBBBBBBBBBBBBBBBBBBBBD      LAlBBD  CBB",
    "                                                           BBBBBBBBBBBBBBBBBBBBBBBrAAAAP.CBBD      C",
    "                                                           BBBBBBBBBBBBBBBBBBBBBBBBBBBBD+CBBD >   [C",
    "                         4                                                              =CBBD LPsLAl",
    "                                                                                              CrAlBB",
    "                        o                                                                     CBBBBB",
    "P                      LAAAP            1                                                          C",
    "D1                     CBBBD       s                                  3    2   LAAAP           1   C",
    "D                      CBBBD      sb                                           CBBBrAP             C",
    "D         LAAG      GAAlBBBD>    LAAP   <                                     bCBBBBBrP   b        C",
    "D    ]>  LlBBGmmmmmmGBBBBBBrP    CBBD  LAAP ss                           o   LAlBBBBBBD sbb       oC",
    "rAAAAAAAAlBBBGGmmmmGGBBBBBBBrP         CBBrSSSSWWWWWWWWWWWWWWWWWWWSSSSAAAAAAAlBBBBBBBBrAAAP  LAAAAAl",
    "BBBBBBBBBBBBBGGGGGGGGBBBBBBBBD     o  LlBBBSSSSwwwwwwwwwwwwwwwwwwwSSSSBBBBBBBBBBBBBBBBBBBBD  CBBBBBB",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBD    LAAAlBBBBSSSSSwwwwwwwwwwwwwwwwwSSSSSBBBBBBBBBBBBBBBBBBBBDssCBBBBBB",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBD  sLlBBBBBBBBSSSSSSwwwwwwwwwwwwwwwSSSSSSBBBBBBBBBBBBBBBBBBBBDbbCBBBBBB",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBDWWLlBBBBBBBBBSSSSSSSSSSSSSSSSSSSSSSSSSSSBBBBBBBBBBBBBBBBBBBBrAAlBBBBBB",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBrAAlBBBBBBBBBBSSSSSSSSSSSSSSSSSSSSSSSSSSSBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    }; 
    std::vector<std::vector<std::vector<char>>> temlate_1;
    char give_letter(int i, int j, int k);
    char give_generation_letter(int i, int j);
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

