#pragma once

#include <SFML/Graphics.hpp>
#include <string>


const int H = 20;
const int W = 100;
const int size_texture = 73;
const int screenHeight = 600;
const int screenWidth = 1500;
extern std::string TileMap[H];


class Enemy
{
public:
    void set(int x, int y);
    void update(float time, float y);
    void collision();

    sf::Sprite enemy_S;
    sf::Texture enemy_T;
    sf::FloatRect rect;
    float currentFrame;
    float dx, dy;
    float HP;
    float power;
    bool life;
};




