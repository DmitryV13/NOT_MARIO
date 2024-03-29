#pragma once

#include "PLAYER_ANIMATION_SATES.h"
#include "Map.h"
#include "TileMap.h"
#include "Fist.h"
#include "Sword.h"
#include "CombatStaff.h"
#include "Bow.h"
#include "kusaka.h"
#include "EyeEvil.h"
#include "WolfBoss.h"
#include "RedMutant.h"
#include "GeneralInfo.h"

using namespace::sf;


class Player{
private:
    TileMap* sandbox;
    Texture player_T;
    Sprite player_S;

    vector<Weapon*> weapons;
    short chosen_weapon;


    IntRect currentFrame;
    Clock stan_timer;
    Clock animationTimer;
    short animationState;
    bool animationSwitch;

    GeneralInfo* info;
    
    float velocityMax;
    float velocityMin;
    float acceleration;
    float deceleration;
    float gravity;
    float velocityMaxY;

    bool spaceRealeased;
    float jumpVelocity;
    bool onGround;
    bool isJumping;
    short jumpCount;
    short jumpLimit;
    bool isFlying;
    float flyVelocity;

    bool alive;
    short movingDirection;

    void initVariables();
    void initTexture();
    void initSprite();
    void initSprite(Vector2f position);
    //void initWeapon();
    void initAnimation();
    void initPhysics();
public:
    Player(TileMap& map);
    Player(TileMap& map, Vector2f position);
    void initWeapon(const vector<vector<Enemy*>*>& enemies);
    IntRect get_pl_frame();
    // accessors
    const bool& getAnimationSwitch();
    const Vector2f getPosition() const;
    const FloatRect getGlobalBounds() const;
    const Vector2f getVelocity() const;
    const short getHP() const;
    short* getHPp();
    GeneralInfo* getGeneralInfo();


    //modifiers
    void resetVelocityY();
    void setPosition(const float x, const float y);
    void resetJumpAccess();
    void resetNTHJump();
    void resetIsFlying();
    void resetAnimationTimer();
    void setDeceleration(float dec);
    
    void walk(const float dir_x);
    void jump(const float dir_y);
    void fly(const float dir_y);

    bool stan();

    void update(RenderWindow* window, FloatRect view_cords);
    void updatePhysics();
    void updateMovement(RenderWindow* window, FloatRect view_cords);
    void updateAnimation();
    void updateWeapon(RenderWindow* window, FloatRect view_cords);
    void updateProjectiles();
    bool updateCollisionX();
    bool updateCollisionY();
    void updateCollision();

    bool checkStan();

    void render(RenderTarget& target);
    void renderProjectiles(RenderTarget& target);

    void change_weapon(short count);
    void changeHP(short z);
};