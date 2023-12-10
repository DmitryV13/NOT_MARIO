#pragma once
#include "Map.h"
#include "TileMap.h"
#include "laser_weapon.h"
#include "Player.h"

using sf::Sprite;
using sf::RenderWindow;
using sf::FloatRect;
using sf::View;
using sf::Texture;
using sf::IntRect;
using sf::Clock;

enum ENEMY_ANIMATION_STATES
{
	ENEMY_IDLE = 0,
	ENEMY_MOVING,
	ENEMY_MOVING_DOWN,
	ENEMY_JUMPING,
	ENEMY_FALLING,
	ENEMY_ATTENTION,
	ENEMY_SHOT,
	ENEMY_SLEEP,
	ENEMY_BITE

};


class Enemy
{
protected:
	TileMap* sandbox;
	Player* player_;
	Texture Enemy_T;
	Sprite Enemy_S;
	IntRect current_frame;
	Clock animation_timer;
	short animation_state;
	bool animation_switch;
	short HP;
	short attack_;

	sf::Vector2f start_position;
	int step_left;
	int step_right;
	int attention_counter;
	int max_step{1000};
	bool jump_tile;
	float moving;
	int animation_counter_think;
	sf::Vector2f displacement;
	float displacement_max;
	float displacement_min;
	float acceleration;
	float deceleration;
	float gravity;
	float velocity_max_y;
	float jump_velocity;
	bool on_ground;
	//enemy
	virtual void init_physics();
	void init_animation();
	void init_variables();
	//virtual
	virtual void init_texture() = 0;
	virtual void init_sprite() = 0;

public:
	//Enemy
	bool looks_to_the_left;
	bool looks_to_the_right;
	sf::Vector2f generate_random_start_position(int mapWidth, int mapHeight);
	Enemy(TileMap& map, Player&);
	const bool& get_animation_switch();
	sf::Vector2f get_position() const;
	const FloatRect get_global_bounds() const;
	void set_position(const float x, const float y);
	void reset_jump_access();
	void render(sf::RenderTarget& target);
	void update();
	bool update_collision_x();
	bool update_collision_x_jump();
	bool update_collision_y();
	void reset_animation_timer();
	virtual void walk(const float dir_x);
	virtual void jump(const float dir_y);
	bool player_contact();
	auto sting() -> bool;


	virtual void jump_towards_player();
	virtual void changeHP(short);

	//virtual
	virtual void reset_attention() = 0;
	virtual ~Enemy() = default;
	virtual void shot() = 0;
	virtual void clear_shot() = 0;
	virtual void attack() = 0;
	virtual bool search_for_enemies() = 0;
	virtual void update_physics();
	virtual void update_movement() = 0;
	virtual void update_animation() = 0;
};
