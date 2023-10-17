#include "stdafx.h"
#include "TileFactory.h"

sf::IntRect TileFactory::initRect_tile(char tile_C) {
    if (tile_C == 'B') {

        return sf::IntRect(100, 21, 73, 73);

    }
    if (tile_C == 'C') {

        return sf::IntRect(186, 21, 73, 73);

    }
    if (tile_C == 'D') {

        return sf::IntRect(270, 21, 73, 73);

    }
    if (tile_C == 'E') {

        return sf::IntRect(100, 105, 73, 73);

    }
    if (tile_C == 'F') {

        return sf::IntRect(186, 105, 73, 73);

    }
    if (tile_C == 'G') {

        return sf::IntRect(270, 105, 73, 73);

    }
    if (tile_C == 'H') {

        return sf::IntRect(100, 191, 73, 73);

    }
    if (tile_C == 'I') {

        return sf::IntRect(186, 191, 73, 73);

    }
    if (tile_C == 'J') {

        return sf::IntRect(270, 191, 73, 73);

    }
    if (tile_C == 'K') {

        return sf::IntRect(355, 191, 73, 73);

    }
    if (tile_C == 'L') {

        return sf::IntRect(18, 191, 73, 73);

    }
    if (tile_C == 'M') {

        return sf::IntRect(355, 275, 73, 73);

    }
    if (tile_C == 'N') {

        return sf::IntRect(18, 275, 73, 73);

    }
    if (tile_C == 'O') {

        return sf::IntRect(100, 275, 73, 73);

    }
    if (tile_C == 'P') {

        return sf::IntRect(186, 275, 73, 73);

    }
    if (tile_C == 'Q') {

        return sf::IntRect(272, 275, 73, 73);

    }
}

TileFactory::TileFactory() {
    std::string template_1[20] = {
  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAF",
  "F                                                                                                 F",
  "F                                                                                                 F",
  "F                                                                                                 F",
  "F                                                                                                 F",
  "F                                                                                                 F",
  "F                                                                                                 F",
  "F   FFF     FFF      FFFFF     FFFFFFFFFFF          FFF     FFF       FFF      FFFFFFF            F",
  "F   FFFF    FFF     FFFFFFF    FFFFFFFFFFF          FFFF   FFFF      FFFFF     FFFFFFFF           F",
  "F   FFFFF   FFF    FF     FF       FFF              FFFFF FFFFF     FFF FFF    FFF   FF           F",
  "F   FFFFFFFFFFF   FFF     FFF      FFF      FFFFF   FFF FFF FFF    FFF   FFF   FFFFFFFF           F",
  "F   FFF   FFFFF    FF     FF       FFF              FFF     FFF    FFFFFFFFF   FFFFFF             F",
  "F   FFF    FFFF     FFFFFFF        FFF              FFF     FFF   FFF     FFF  FFF FFF            F",
  "F   FFF     FFF        FFF         FFF              FFF     FFF   FFF     FFF  FFF  FFF  F F F    F",
  "F                                                        F                                        F",
  "FF                  FFF                                FFF                                        F",
  "F F              FFFFFFF            F          F     FFFFF                                        F",
  "FJKCCLHFFFJKCCCCCCLHFFFFFFFFJKFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
  "FIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIF",
    };
    Tile tile_B(initRect_tile('B'), 'B');
    Tile tile_C(initRect_tile('C'), 'C');
    Tile tile_D(initRect_tile('D'), 'D');
    Tile tile_E(initRect_tile('E'), 'E');
    Tile tile_F(initRect_tile('F'), 'F');
    Tile tile_G(initRect_tile('G'), 'G');
    Tile tile_H(initRect_tile('H'), 'H');
    Tile tile_I(initRect_tile('I'), 'I');
    Tile tile_J(initRect_tile('J'), 'J');
    Tile tile_K(initRect_tile('K'), 'K');
    Tile tile_L(initRect_tile('L'), 'L');
    Tile tile_M(initRect_tile('M'), 'M');
    Tile tile_N(initRect_tile('N'), 'N');
    Tile tile_O(initRect_tile('O'), 'O');
    Tile tile_P(initRect_tile('P'), 'P');
    Tile tile_Q(initRect_tile('Q'), 'Q');

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 100; j++) {
            if (template_1[i][j] == 'B') { tile_map_inFactory[i][j] = tile_B; }
            if (template_1[i][j] == 'C') { tile_map_inFactory[i][j] = tile_C; }
            if (template_1[i][j] == 'D') { tile_map_inFactory[i][j] = tile_D; }
            if (template_1[i][j] == 'E') { tile_map_inFactory[i][j] = tile_E; }
            if (template_1[i][j] == 'F') { tile_map_inFactory[i][j] = tile_F; }
            if (template_1[i][j] == 'G') { tile_map_inFactory[i][j] = tile_G; }
            if (template_1[i][j] == 'H') { tile_map_inFactory[i][j] = tile_H; }
            if (template_1[i][j] == 'I') { tile_map_inFactory[i][j] = tile_I; }
            if (template_1[i][j] == 'J') { tile_map_inFactory[i][j] = tile_J; }
            if (template_1[i][j] == 'K') { tile_map_inFactory[i][j] = tile_K; }
            if (template_1[i][j] == 'L') { tile_map_inFactory[i][j] = tile_L; }
            if (template_1[i][j] == 'M') { tile_map_inFactory[i][j] = tile_M; }
            if (template_1[i][j] == 'N') { tile_map_inFactory[i][j] = tile_N; }
            if (template_1[i][j] == 'O') { tile_map_inFactory[i][j] = tile_O; }
            if (template_1[i][j] == 'P') { tile_map_inFactory[i][j] = tile_P; }
            if (template_1[i][j] == 'Q') { tile_map_inFactory[i][j] = tile_Q; }
        }
    }
}

