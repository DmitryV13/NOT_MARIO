#include "stdafx.h"
#include "TileFactory.h"

sf::IntRect TileFactory::initRect_tile(char tile_C) {
    if (tile_C == 'A') { return sf::IntRect(66, 2, 60, 60); }
    if (tile_C == 'B') { return sf::IntRect(2, 2, 60, 60); }
    if (tile_C == 'C') { return sf::IntRect(130, 2, 60, 60); }
    if (tile_C == 'D') { return sf::IntRect(194, 2, 60, 60); }
    if (tile_C == 'L') { return sf::IntRect(258, 2, 60, 60); }
    if (tile_C == 'P') { return sf::IntRect(322, 2, 60, 60); }
}

void TileFactory::generation_map(std::string map[40][201]) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double random_number;
    double probability = 0.36;
    int helper = 0;
    int i = 20;
    for (int j = 0; j < 200; j++) {
        random_number = dist(gen);
        if (random_number <= probability / 2 && i < 39) {
            i++;
            map[i][j] = "A";
            if (i > 0 && j > 1) {
                if (map[i - 1][j - 2] == " ") {
                    map[i - 1][j - 1] = " ";
                    map[i][j - 1] = "A";
                }
                else map[i - 1][j - 1] = "P";
            }
            helper = i + 1;
            while (helper <= 39) {
                map[helper][j] = "B";
                helper++;
            }
            helper = i - 1;
            while (helper >= 0) {
                map[helper][j] = " ";
                helper--;
            }
        }
        else if (random_number > probability / 2 && random_number <= probability && i > 0) {
            i--;
            map[i][j] = "L";
            helper = i + 1;
            while (helper <= 39) {
                map[helper][j] = "B";
                helper++;
            }
            helper = i - 1;
            while (helper >= 0) {
                map[helper][j] = " ";
                helper--;
            }
        }
        else {
            map[i][j] = "A";
            helper = i + 1;
            while (helper <= 39) {
                map[helper][j] = "B";
                helper++;
            }
            helper = i - 1;
            while (helper >= 0) {
                map[helper][j] = " ";
                helper--;
            }
        }
    }
    // std::uniform_real_distribution<float> dist_i(20, 30);
    // std::uniform_real_distribution<float> dist_j(20, 180);
    // std::uniform_real_distribution<float> dist_ch(100, 1000);
    // int k = dist_i(gen);
    // int l = dist_j(gen);
    // int ch = dist_ch(gen);
    // while (ch >= 0) {
    //     ch--;
    //     if (k < 35 && k > 20 && l > 5 && l < 195) {
    //         for (int i = k - 1; i <= k + 1; i++) {
    //             for (int j = l - 1; j <= l + 1; j++) {
    //                 map[i][j] = " ";
    //             }
    //         }
    //     }
    //     random_number = dist(gen);
    //     if (random_number <= 0.100 && k <=38) {
    //         k++;
    //     }
    //     if (random_number > 0.100 && random_number <= 0.200 && k<=38 && l <=195) {
    //         k++;
    //         l++;
    //     }
    //     if (random_number > 0.200 && random_number < 0.300 && k <=38 && l >= 5) {
    //         k++;
    //         l--;
    //     }
    //     if (random_number > 0.300 && random_number <= 0.500 && l >= 5 ) {
    //         l--;
    //     }
    //     if (random_number > 0.500 && random_number <= 0.600 && k >= 20 && l >= 5) {
    //         k--;
    //         l--;
    //     }
    //     if (random_number > 0.600 && random_number < 0.700 && k >= 20) {
    //         k--;
    //     }
    //     if (random_number > 0.700 && random_number < 0.800 && k >= 20 && l <= 195) {
    //         k--;
    //         l++;
    //     }
    //     if (random_number >= 0.800 && random_number <= 1.0 && l <= 195) {
    //         l++;
    //     }
    // } 
}

TileFactory::TileFactory() {
    std::string template_1[40] = {
  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
  "A                                                                                                 AA                                                                                                 AAA",
  "A                                                                                                 AA                                                                                                 AAA",
  "A                                                                                                 AA                                                                                                 AAA",
  "A                                                                                                 AA                                                                                                 AAA",
  "A                                                                                                 AA                                                                                                 AAA",
  "A                                                                                                 AA                                                                                                 AAA",
  "A   FFF     FFF      FFFFF     FFFFFFFFFFF          FFF     FFF       FFF      FFFFFFF            AA   FFF     FFF      FFFFF     FFFFFFFFFFF          FFF     FFF       FFF      FFFFFFF            AAA",
  "A   FFFF    FFF     FFFFFFF    FFFFFFFFFFF          FFFF   FFFF      FFFFF     FFFFFFFF           AA   FFFF    FFF     FFFFFFF    FFFFFFFFFFF          FFFF   FFFF      FFFFF     FFFFFFFF           AAA",
  "A   FFFFF   FFF    FF     FF       FFF              FFFFF FFFFF     FFF FFF    FFF   FF           AA   FFFFF   FFF    FF     FF       FFF              FFFFF FFFFF     FFF FFF    FFF   FF           AAA",
  "A   FFFFFFFFFFF   FFF     FFF      FFF      FFFFF   FFF FFF FFF    FFF   FFF   FFFFFFFF           AA   FFFFFFFFFFF   FFF     FFF      FFF      FFFFF   FFF FFF FFF    FFF   FFF   FFFFFFFF           AAA",
  "A   FFF   FFFFF    FF     FF       FFF              FFF     FFF    FFFFFFFFF   FFFFFF             AA   FFF   FFFFF    FF     FF       FFF              FFF     FFF    FFFFFFFFF   FFFFFF             AAA",
  "A   FFF    FFFF     FFFFFFF        FFF              FFF     FFF   FFF     FFF  FFF FFF            AA   FFF    FFFF     FFFFFFF        FFF              FFF     FFF   FFF     FFF  FFF FFF            AAA",
  "A   FFF     FFF      FFFFF         FFF              FFF     FFF   FFF     FFF  FFF  FFF  F F F    AA   FFF     FFF      FFFFF         FFF              FFF     FFF   FFF     FFF  FFF  FFF  F F F    AAA",
  "A                                                                                                 AA                                                                                                 AAA",
  "A                   FFF                                                                           AA                   FFF                                                                           AAA",
  "A                FFF                                                                              AA                FFF                                                                              AAA",
  "AJKCCLHFFFJKCCCCCCLHFFFFFFFFJKFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAAJKCCLHFFFJKCCCCCCLHFFFFFFFFJKFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAAA",
  "AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
  "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
    };

    std::string template_3[40][201];
    generation_map(template_3);
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 200; j++) {
            std::cout << template_3[i][j];
        }
        std::cout << std::endl;
    }

    Tile tile_A(initRect_tile('A'), 'A', 'A');
    Tile tile_B(initRect_tile('B'), 'B', 'B');
    Tile tile_C(initRect_tile('C'), 'C', 'C');
    Tile tile_D(initRect_tile('D'), 'D', 'D');
    Tile tile_L(initRect_tile('L'), 'L', 'L');
    Tile tile_P(initRect_tile('P'), 'P', 'P');

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 200; j++) {
            if (template_3[i][j] == "A") { tile_map_inFactory[i][j] = tile_A; }
            if (template_3[i][j] == "B") { tile_map_inFactory[i][j] = tile_B; }
            if (template_3[i][j] == "C") { tile_map_inFactory[i][j] = tile_C; }
            if (template_3[i][j] == "D") { tile_map_inFactory[i][j] = tile_D; }
            if (template_3[i][j] == "L") { tile_map_inFactory[i][j] = tile_L; }
            if (template_3[i][j] == "P") { tile_map_inFactory[i][j] = tile_P; }
        }
    }
}

