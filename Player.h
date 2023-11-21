#pragma once
#include "Map.h"
#include "TileMap.h"
#include "Sword.h"

using namespace::sf;

enum PLAYER_ANIMATION_STATES{IDLE_LEFT=0, IDLE_RIGHT, MOVING_LEFT, MOVING_RIGHT, MOVING_DOWN, MOVING_UP, JUMPING, FALLING};


class Player {
private:
    TileMap* sandbox;

    Texture player_T;
    Sprite player_S;

    Sword* sword;

    IntRect currentFrame;
    Clock animationTimer;
    short animationState;
    bool animationSwitch;

    Vector2f velocity;
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

    short movingDirection;

    void initVariables();
    void initTexture();
    void initSprite();
    void initWeapon();
    void initAnimation();
    void initPhysics();
public:
    Player(TileMap& map);

    // accessors
    const bool& getAnimationSwitch();
    const Vector2f getPosition() const;
    const FloatRect getGlobalBounds() const;
    const Vector2f getVelocity() const;

    //modifiers
    void resetVelocityY();
    void setPosition(const float x, const float y);
    void resetJumpAccess();
    void resetNTHJump();
    void resetIsFlying();
    
    //void updateMovement(double time, RenderWindow& window);
    void render(RenderTarget& target);
    void walk(const float dir_x);
    void jump(const float dir_y);
    void fly(const float dir_y);
    void update();
    void updatePhysics();
    void updateMovement();
    void updateAnimation();
    void updateSword();
    bool updateCollisionX();
    bool updateCollisionY();
    void updatePresence();

    void resetAnimationTimer();
    
    void attack();
};