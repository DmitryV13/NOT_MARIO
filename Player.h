#pragma once
#include "Map.h"

using sf::Sprite;
using sf::RenderWindow;
using sf::FloatRect;
using sf::View;
using sf::Texture;
using sf::IntRect;
using sf::Clock;


enum PLAYER_ANIMATION_STATES{IDLE=0, MOVING_LEFT, MOVING_RIGHT, MOVING_DOWN, MOVING_UP, JUMPING, FALLING};


class Player {
private:
    //Map levelMap;
    //double absoluteRight;
    //double absoluteBottom;

    Texture player_T;
    Sprite player_S;

    IntRect currentFrame;
    Clock animationTimer;
    short animationState;
    bool animationSwitch;

    sf::Vector2f velocity;
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
    //FloatRect coordinates;
    //double speedX;
    //double speedY;
    //double acceleration = 0.0009;
    //double heightCoeficient = 2;
    //bool onGround;
    //double currentFrame;
    void initVariables();
    void initTexture();
    void initSprite();
    void initAnimation();
    void initPhysics();

public:
    //Player(Texture& texture, RenderWindow& window_, Map& levelMap_);
    Player();

    // accessors
    const bool& getAnimationSwitch();
    const sf::Vector2f getPosition() const;
    const FloatRect getGlobalBounds() const;

    //modifiers
    void resetVelocityY();
    void setPosition(const float x, const float y);
    void resetJumpAccess();
    void resetNTHJump();

    
    //void updateMovement(double time, RenderWindow& window);
    void render(sf::RenderTarget& target);
    void move(const float dir_x, const float dir_y);
    void jump(const float dir_y);
    void update();
    void updatePhysics();
    void updateMovement();
    void updateAnimation();
    void resetAnimationTimer();
    
    //void checkCollisionX();;
    //void checkCollisionY();
    //void fallingTest();
    //void changeFrames(double& time);
    //void checkingBordersX();
    //void checkingBordersY();
};