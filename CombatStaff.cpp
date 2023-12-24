#include "stdafx.h"
#include "CombatStaff.h"

    CombatStaff::CombatStaff(Vector2f player_position, FloatRect player_bounds, TileMap* sandbox_, const vector<vector<Enemy*>*>& enemies_)
        :enemies(enemies_), sandbox(sandbox_) {
        initTexture();
        initSprite(player_position, player_bounds);
        initVariables();
    }

    void CombatStaff::initTexture(){
        if (!staff_T.loadFromFile("Textures/Weapons/staff1.png")) {
            std::cout << "Error -> Sword -> couldn't load staff texture" << std::endl;
        }
    }
    
    void CombatStaff::initSprite(Vector2f player_position, FloatRect player_bounds){
        staff_S.setTexture(staff_T);
        currentFrame = IntRect(0, 0, 18, 71);
        staff_S.setTextureRect(currentFrame);
        staff_S.setOrigin(6, 42);
        staff_S.setPosition(player_position.x + 21, player_position.y + 43);
    }
    
    void CombatStaff::initVariables(){
        attack_activation = false;
        side_of_attack = 0;
        previous_side = 0;
    }
    
    void CombatStaff::initAnimation(){
        animationTimer.restart();
    }
    
    void CombatStaff::render(RenderTarget& target){
        target.draw(staff_S);
    }

    void CombatStaff::renderProjectiles(RenderTarget& target){
        for (auto& i : projectiles) {
            i->render(target);
        }
    }
    
    void CombatStaff::update(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords){
        updatePosition(player_position, player_side, window, view_cords);
        updateAnimation();
    }

    void CombatStaff::updatePosition(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords){
        if (player_side == PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
            currentFrame.width = 18.f;
            if (previous_side == 0) {
                previous_side = 1;
                currentFrame.left = 0.f;
            }
            staff_S.setOrigin(6, 42);
            staff_S.setTextureRect(currentFrame);
            staff_S.setPosition(player_position.x + 21, player_position.y + 43);
        }
        else {
            if (previous_side == 1) {
                previous_side = 0;
                currentFrame.left = 18.f;
            }
            currentFrame.width = -18.f;
            staff_S.setOrigin(12,42);
            staff_S.setTextureRect(currentFrame);
            //21-82
            staff_S.setPosition(player_position.x + 27, player_position.y + 43);
        }
    }
    
    void CombatStaff::updateAnimation(){
        if (attack_activation) {
            if (side_of_attack == PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
                if (animationTimer.getElapsedTime().asSeconds() >= 0.04f) {
                    currentFrame.top = 0;
                    currentFrame.left += 18;

                    if (currentFrame.left >= 72.f) {
                        currentFrame.left = 0.f;
                        attack_activation = false;
                    }
                    currentFrame.width = 18;
                    animationTimer.restart();
                    staff_S.setTextureRect(currentFrame);
                }
            }
            else if (side_of_attack == PLAYER_ANIMATION_STATES::MOVING_LEFT) {
                if (animationTimer.getElapsedTime().asSeconds() >= 0.04f) {
                    currentFrame.top = 0;
                    currentFrame.left += 18;
                    if (currentFrame.left >= 90.f) {
                        currentFrame.left = 18.f;
                        attack_activation = false;
                    }
                    currentFrame.width = -18;
                    animationTimer.restart();
                    staff_S.setTextureRect(currentFrame);
                }
            }
        }
    }

    void CombatStaff::updateProjectiles(){
        for (int i = 0; i < projectiles.size(); i++) {
            projectiles[i]->update();
            if (projectiles[i]->updateHit()) {
                
            }
            if (projectiles[i]->updateCollision()) {
                delete *(projectiles.begin()+i);
                projectiles.erase(projectiles.begin() + i);
            }
        }
    }
    
    void CombatStaff::attack(short side_attack, Vector2f mouse_pos, FloatRect view_cords, bool is_btn_pressed){
        if (is_btn_pressed) {
            this->side_of_attack = side_attack;
            attack_activation = true;
            if (animationTimer.getElapsedTime().asSeconds() >= 0.04f) {
                if (projectiles.size() > 30) {
                    delete projectiles[0];
                    projectiles.erase(projectiles.begin());
                }
                projectiles.push_back(new Projectile(staff_S.getPosition()
                    , Vector2f(mouse_pos.x + (view_cords.left - view_cords.width / 2)
                        , mouse_pos.y + (view_cords.top - view_cords.height / 2)), sandbox
                    , enemies));

            }
        }
    }
    