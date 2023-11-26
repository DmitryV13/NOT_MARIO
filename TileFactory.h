#pragma once
#include "Tile.h"
#include "random"

class TileFactory {
private:

    
    float template_W;
    float template_H;
    void generation_map(std::vector<std::vector<char>>& map);
    

public:
    
    TileFactory(float temp_W, float temp_H);
    std::vector<std::vector<char>> generation_template;
    std::string template_test_1[35];
    std::string a[35] = {

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
    char give_letter(int i, int j);
};

