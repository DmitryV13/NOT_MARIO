#pragma once
#include "Enemy.h"

class Ghost : public Enemy
{
public:
    void set(int x, int y) ;
    void update(float time, float y) ;
   Ghost(sf::Texture& t, int x, int y);

    //~Gost() = default;
    //void battle(float HP_PLAYER, float power_player);
    //void MoveEnemy(std::string map[H], float startX, int startY);
};


