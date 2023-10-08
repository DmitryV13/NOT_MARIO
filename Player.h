#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
#include <SFML/Graphics.hpp>
using sf::Sprite;
using sf::RenderWindow;
using sf::FloatRect;
using sf::View;
using sf::Texture;

class Player {
public:
    Map levelMap;
    double absoluteRight;
    double absoluteBottom;

    Sprite player_S;
    FloatRect coordinates;
    double speedX;
    double speedY;
    double acceleration = 0.0009;
    double heightCoeficient = 2;
    bool onGround;
    double currentFrame;

    Player(Texture& texture, RenderWindow& window_, Map& levelMap_);

    void update(double time, RenderWindow& window);
    void checkCollisionX();;
    void checkCollisionY();
    void fallingTest();
    void changeFrames(double& time);
    void checkingBordersX();
    void checkingBordersY();
};

#endif