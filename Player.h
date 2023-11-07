#pragma once
#include "Map.h"
#include "TileMap.h"

using sf::Sprite;
using sf::RenderWindow;
using sf::FloatRect;
using sf::View;
using sf::Texture;
using sf::IntRect;
using sf::Clock;


enum PLAYER_ANIMATION_STATES{IDLE_LEFT=0, IDLE_RIGHT, MOVING_LEFT, MOVING_RIGHT, MOVING_DOWN, MOVING_UP, JUMPING, FALLING};


class Player {
private:
    TileMap* sandbox;

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
    bool isFlying;
    float flyVelocity;

    bool movingDirection;
    //FloatRect coordinates;
    //double speedX;
    //double speedY;
    //double acceleration = 0.0009;
    //double heightCoeficient = 2;
    //bool on_ground;
    //double current_frame;
    void initVariables();
    void initTexture();
    void initSprite();
    void initAnimation();
    void initPhysics();

public:
    //Player(Texture& texture, RenderWindow& window_, Map& levelMap_);
    Player(TileMap& map);

    // accessors
    const bool& getAnimationSwitch();
    const sf::Vector2f getPosition() const;
    const FloatRect getGlobalBounds() const;
    const sf::Vector2f getVelocity() const;

    //modifiers
    void resetVelocityY();
    void setPosition(const float x, const float y);
    void resetJumpAccess();
    void resetNTHJump();
    void resetIsFlying();
    
    //void update_movement(double time, RenderWindow& window);
    void render(sf::RenderTarget& target);
    void walk(const float dir_x);
    void jump(const float dir_y);
    void fly(const float dir_y);
    void update();
    void updatePhysics();
    void updateMovement();
    void updateAnimation();
    bool updateCollisionX();
    bool updateCollisionY();
    void updatePresence();
    void resetAnimationTimer();
    
    //void checkCollisionX();;
    //void checkCollisionY();
    //void fallingTest();
    //void changeFrames(double& time);
    //void checkingBordersX();
    //void checkingBordersY();
};