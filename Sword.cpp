#include "stdafx.h"
#include "Sword.h"



    Sword::Sword(Vector2f player_position, FloatRect player_bounds, const vector<vector<Enemy*>*>& enemies_, TextureManager* t_manager, int index, string name)
    :enemies(enemies_) {
        initSprite(player_position, player_bounds, t_manager, index, name);
        initVariables();
    }
    
    void Sword::initSprite(Vector2f player_position, FloatRect player_bounds, TextureManager* t_manager, int index, string name) {
        sword_S.setTexture(t_manager->getTexture(index, name));
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
        side_of_attack = PLAYER_ANIMATION_STATES::IDLE_LEFT;
        previous_side = PLAYER_ANIMATION_STATES::IDLE_RIGHT;
    }
    
    void Sword::initAnimation() {
        animationTimer.restart();
    }
    
    void Sword::render(RenderTarget& target) {
        target.draw(sword_S);
    }
    
    void Sword::update(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords){
        updatePosition(player_position, player_side, window, view_cords);
        updateAnimation();
    }
    
    void Sword::updatePosition(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords) {
        Vector2f mouse_pos(Mouse::getPosition(*window));
        if (player_side == PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
            currentFrame.width = 92.f;
            if (previous_side == PLAYER_ANIMATION_STATES::MOVING_LEFT || previous_side == PLAYER_ANIMATION_STATES::IDLE_RIGHT) {
                previous_side = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
                currentFrame.left = 0.f;
            }
            sword_S.setOrigin(10, 64);
            sword_S.setTextureRect(currentFrame);
            sword_S.setPosition(player_position.x + 27, player_position.y + 41 );
            sword_S.setRotation(180 / 3.14 * std::atan2(mouse_pos.y + (view_cords.top - view_cords.height / 2) - sword_S.getPosition().y, mouse_pos.x + (view_cords.left - view_cords.width / 2) - sword_S.getPosition().x));
        }
        else {
            if (previous_side == PLAYER_ANIMATION_STATES::MOVING_RIGHT || previous_side == PLAYER_ANIMATION_STATES::IDLE_RIGHT) {
                previous_side = PLAYER_ANIMATION_STATES::MOVING_LEFT;
                currentFrame.left = 92.f;
            }
            currentFrame.width = -92.f;
            sword_S.setOrigin(82, 64);
            sword_S.setTextureRect(currentFrame);
            //21-82
            sword_S.setPosition(player_position.x +21, player_position.y +41);
            sword_S.setRotation(180 + 180 / 3.14 * std::atan2(mouse_pos.y + (view_cords.top - view_cords.height / 2) - sword_S.getPosition().y, mouse_pos.x + (view_cords.left - view_cords.width / 2) - sword_S.getPosition().x));
        }
    }
    
    void Sword::updateAnimation() {
        if (attack_activation) {
            if (side_of_attack == PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
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
            else if (side_of_attack == PLAYER_ANIMATION_STATES::MOVING_LEFT) {
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
    
    void Sword::attack(short side_attack, Vector2f mouse_pos, FloatRect view_cord, bool is_btn_pressed) {
        //3 - right
        //2 - left
        if (is_btn_pressed) {
            this->side_of_attack = side_attack;
            attack_activation = true;

            for (auto enemy_l : enemies)
            {
                for (auto enemy : *enemy_l) {
                    if (sword_S.getGlobalBounds().intersects((enemy)->get_global_bounds())) {
                        enemy->changeHP(10);
                    }
                }
            }
        }
    }
    