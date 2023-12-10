#include "Enemy.h"
#include "Zombi.h"

extern enum direction { left, right };
extern direction zombi_direction = right;
Zombi::Zombi(sf::Texture& t, int x, int y) {
    HP = static_cast<float>(300);
    dx = static_cast<float>(0.7);
    dy = static_cast<float>(0.02);
    power = static_cast<float>(50);
    life = true;
    currentFrame = 0;
    enemy_S.setTexture(t);
    rect = sf::FloatRect(static_cast<float>(x), static_cast<float>(y), static_cast<float>(20), static_cast<float>(60));
}

void Zombi::update(float time, float y)
{
    rect.top = y;
    float newX = rect.left + dx * time;
    bool collisionDetected = false;

    if (newX >= 0 && newX <= (W * size_texture - rect.width)) {

        for (int j = (int)(newX / size_texture); j < (int)((newX + rect.width) / size_texture); j++) {
            for (int i = (int)(rect.top / size_texture); i < (int)((rect.top + rect.height) / size_texture); i++) {
                if (TileMap[i][j + 1] == 'B' || TileMap[i][j + 1] == 'G' || TileMap[i][j + 1] == 'D' || 
                    TileMap[i][j + 1] == 'F') {
                    collisionDetected = true;
                    break;
                }
            }
            if (collisionDetected) {
                break;
            }
        }
    }
    else {
        collisionDetected = true;
    }

    if (collisionDetected) {
        dx = -dx;
        if (dx > 0) {
            zombi_direction = right;
        }
        else if (dx < 0) {
            zombi_direction = left;
        }
    }
    else {

        rect.left = newX;
    }

    collision();

    currentFrame += time * static_cast<float>(0.007);
    if (currentFrame > 6) currentFrame -= 6;


    if (dx > 0) {
        zombi_direction = right;
    }
    else if (dx < 0) {
        zombi_direction = left;
    }
    if (zombi_direction == left) {

        enemy_S.setTextureRect(sf::IntRect(50 * static_cast<int>(currentFrame)+50, 0, -50, 60));
    }
    else {

        enemy_S.setTextureRect(sf::IntRect(50 * static_cast<int>(currentFrame), 0, 50, 60));
    }
    enemy_S.setPosition(rect.left, rect.top);

}
//void Zombi::set(int x, int y)
//{
//
//    enemy_S.setTexture(enemy_T);
//    rect = sf::FloatRect(x, y, 20, 60);
//    currentFrame = 0;
//
//
//}