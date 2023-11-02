#pragma once
#include "Enemy.h"

class Zombi :public  Enemy
{
public:
    void set(int x, int y) ;
    void update(float time, float y);
    Zombi(sf::Texture& t, int x, int y);
    //~Zombi() = default;

private:

};


