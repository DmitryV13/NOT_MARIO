#include "Ghost.h"
#include "Enemy.h"
extern enum direction { left, right };
extern direction ghost_direction = right;

Ghost::Ghost(sf::Texture& t, int x, int y) {
    HP = static_cast<float>(100);
    dx = static_cast<float>(0.01);
    dy = static_cast<float>(0.01);
    power = static_cast<float>(20);
    life = true;
    enemy_S.setTexture(t);
    rect = sf::FloatRect(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)), sf::Vector2f(static_cast<float>(60), static_cast<float>(60)));
}
//void Gost::set(int x, int y)
//{
//
//    enemy_S.setTexture(enemy_T);
//    rect = sf::FloatRect(sf::Vector2f(x, y), sf::Vector2f(60, 60));
//    currentFrame = 0;
//
//}

void Ghost::update(float time, float y)
{

    rect.position.y = y;
    rect.position.x += dx * time;
    collision();
    //currentFrame += time * 0.005;
     //if (currentFrame > 2)currentFrame -= 2;
    if (dx > 0) {
        ghost_direction = right;
    }
    else if (dx < 0) {
        ghost_direction = left;
    }
    if (ghost_direction == left) {
        enemy_S.setTextureRect(sf::IntRect(sf::Vector2i(60, 0), sf::Vector2i(-60, 60)));
    }
    else {
        enemy_S.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(60, 60)));

    }


    enemy_S.setPosition(sf::Vector2f(rect.position.x, rect.position.y));

}
