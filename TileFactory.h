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
};

