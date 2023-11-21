#include "stdafx.h"
#include "Sword.h"



Sword::Sword(Vector2f player_position, FloatRect player_bounds) {
    initTexture();
    initSprite(player_position, player_bounds);
    initVariables();
}

void Sword::initTexture() {
    if (!sword_T.loadFromFile("Textures/sword.png")) {
        std::cout << "Error -> Sword -> couldn't load sword texture" << std::endl;
    }
}

void Sword::initSprite(Vector2f player_position, FloatRect player_bounds) {
    sword_S.setTexture(sword_T);
    currentFrame = IntRect(0, 0, 92, 112);
    sword_S.setTextureRect(currentFrame);
    // 10 64 sword's grip
    // 27 41 hero's hand
    // y= py-(64-41)
    // x= px-(10-27)
    sword_S.setPosition(player_position.x + 17, player_position.y - 23);
}

void Sword::initVariables() {
    attack_activation = false;
    side_of_attack = 0;
    previous_side = 0;
}

void Sword::initAnimation() {
    animationTimer.restart();
}

void Sword::render(RenderTarget& target) {
    target.draw(sword_S);
}

void Sword::updatePosition(Vector2f player_position, short player_side) {
    if (player_side == 3) {
        currentFrame.width = 92.f;
        if (previous_side == 0) {
            previous_side = 1;
            currentFrame.left = 0.f;
        }
        //currentFrame.left = 0.f;

        sword_S.setTextureRect(currentFrame);
        sword_S.setPosition(player_position.x + 17, player_position.y - 23);
    }
    else {
        if (previous_side == 1) {
            previous_side = 0;
            currentFrame.left = 92.f;
        }
        currentFrame.width = -92.f;
        sword_S.setTextureRect(currentFrame);
        //21-82
        sword_S.setPosition(player_position.x - 61, player_position.y - 23);
    }
}

void Sword::updateAnimation() {
    if (attack_activation) {
        if (side_of_attack == 3) {
            if (animationTimer.getElapsedTime().asSeconds() >= 0.03f) {
                currentFrame.top = 0;
                currentFrame.left += 92;
                if (currentFrame.left >= 552.f) {
                    currentFrame.left = 0.f;
                    attack_activation = false;
                }
                currentFrame.width = 92;
                animationTimer.restart();
                sword_S.setTextureRect(currentFrame);
            }
        }
        else if (side_of_attack == 2) {
            if (animationTimer.getElapsedTime().asSeconds() >= 0.03f) {
                currentFrame.top = 0;
                currentFrame.left += 92;
                if (currentFrame.left >= 644.f) {
                    currentFrame.left = 92.f;
                    attack_activation = false;
                }
                currentFrame.width = -92;
                animationTimer.restart();
                sword_S.setTextureRect(currentFrame);
            }
        }
    }
}

void Sword::attack(short side_attack) {
    //3 - right
    //2 - left
    this->side_of_attack = side_attack;
    attack_activation = true;
}
