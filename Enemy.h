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

enum Enemy_ANIMATION_STATES { ENEMY_IDLE = 0, ENEMY_MOVING_LEFT, ENEMY_MOVING_RIGHT,
	ENEMY_MOVING_DOWN, ENEMY_MOVING_UP, ENEMY_JUMPING, ENEMY_FALLING , ENEMY_ATTENTION};


class Enemy
{
protected:
    TileMap sandbox;
    Texture Enemy_T;
    Sprite Enemy_S;
    Tile pos_Player[TileFactory::n][TileFactory::m];
    IntRect currentFrame;
    Clock animationTimer;
    short animationState;
    bool animationSwitch;
  
    sf::Vector2f startPosition;
    int currentBlockX{0};
    int currentBlockY{0};
    int stepLeft;
    int stepRight;
    int maxStep{ 500 };

    bool jumpTile;
	float moving;

    int iterationStart{ 0 };
    int iterationEnd{ 20 };

    sf::Vector2f displacement;
    float displacementMax;
    float displacementMin;
    float acceleration;
    float deceleration;
    float gravity;
    float velocityMaxY;
    float jumpVelocity;
    bool onGround;
    
    void init_variables();
    virtual void init_texture() = 0;
   
    virtual void init_sprite() = 0;
    void init_animation();
    void init_physics();

public:
	sf::Vector2f generateRandomStartPosition(int mapWidth, int mapHeight);

    Enemy(TileMap& map);
   virtual ~Enemy() = default;

    // accessors
    const bool& get_animation_switch();
    sf::Vector2f getPosition() const;
    const FloatRect getGlobalBounds() const;
   // const sf::Vector2f getVelocity() const;

    //modifiers
    void resetVelocityY();
    void setPosition(const float x, const float y);
    void resetJumpAccess();
    //void resetNTHJump();
    //void resetIsFlying();

    //void updateMovement(double time, RenderWindow& window);
    void render(sf::RenderTarget& target);
    void walk(const float dir_x);
    void jump(const float dir_y);
    void update();
    void updatePhysics();
    void updateMovement();
    void updateAnimation();
    bool updateCollisionX();
    bool updateCollisionY();
    void resetAnimationTimer();


    bool search_for_enemies();
    

    //void checkCollisionX();;
    //void checkCollisionY();
    //void fallingTest();
    //void changeFrames(double& time);
    //void checkingBordersX();
    //void checkingBordersY();
};

