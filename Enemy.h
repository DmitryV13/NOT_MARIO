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

enum Enemy_ANIMATION_STATES {
    ENEMY_IDLE = 0, ENEMY_MOVING_LEFT, ENEMY_MOVING_RIGHT,
    ENEMY_MOVING_DOWN, ENEMY_MOVING_UP, ENEMY_JUMPING, ENEMY_FALLING, ENEMY_ATTENTION
};


class Enemy
{
protected:
    TileMap* sandbox;
    Texture Enemy_T;
    Sprite Enemy_S;
    IntRect current_frame;
    Clock animation_timer;
    short animation_state;
    bool animation_switch;
    sf::Vector2f start_position;
    int step_left;
    int step_right;
    int max_step{ 10000 };

    bool jump_tile;
    float moving;

    sf::Vector2f displacement;
    float displacement_max;
    float displacement_min;
    float acceleration;
    float deceleration;
    float gravity;
    float velocity_max_y;
    float jump_velocity;
    bool on_ground;
    
    virtual void init_texture() = 0;
    virtual void init_sprite() = 0;

    void init_variables();
    void init_animation();
    void init_physics();

public:
    sf::Vector2f generate_random_start_position(int mapWidth, int mapHeight);

    Enemy(TileMap& map);
    virtual ~Enemy() = default;

    const bool& get_animation_switch();
    sf::Vector2f get_position() const;
    const FloatRect get_global_bounds() const;

    void set_position(const float x, const float y);
    void reset_jump_access();


    void render(sf::RenderTarget& target);
    void walk(const float dir_x);
    void jump(const float dir_y);
    void update();
    void update_physics();
    void update_movement();
    void update_animation();
    bool update_collision_x();
    bool update_collision_x_jump();
    bool update_collision_y();
    void reset_animation_timer();
    bool search_for_enemies();

};
