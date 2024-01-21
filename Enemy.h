#pragma once
#include "Map.h"
#include "TileMap.h"
#include "laser_weapon.h"
#include "GeneralInfo.h"

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
	ENEMY_BITE,
	ENEMY_DEATH,
	ENEMY_TAKING_DAMAGE,
	ENEMY_RUN,
	ENEMY_TELEPORT,
	ENEMY_PUNCH,
	ENEMY_DOUBLE_KICK,
	ENEMY_HOWL,
	ENEMY_HIT_EARTH
};

enum class PL_SIDE
{
	LEFT,
	RIGHT
};


class Enemy
{
protected:
	TileMap* sandbox;
	GeneralInfo* player_info;


	Texture Enemy_T;
	Sprite Enemy_S;
	Sprite observation_area;
	Sprite anim_area;
	IntRect current_frame;
	IntRect current_area;
	IntRect standard_frame;
	Clock animation_timer;
	Clock blow_timer;


	short animation_state;
	short animation_state_past;
	bool animation_switch;
	short hp_damage_i;
	short HP;
	short attack_;
	short count_shot;

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
	void init_animation();
	void init_variables();
	void setAt(short at);
	void setHP(short hp);
	//virtual
	virtual void init_physics();
	virtual void init_texture() = 0;
	virtual void init_sprite() = 0;

public:
	//Enemy
	bool looks_to_the_left;
	bool looks_to_the_right;
	sf::Vector2f generate_random_start_position(int mapWidth, int mapHeight);
	Enemy(TileMap& map, GeneralInfo* player_info_);
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
	bool player_contact();
	auto sting() -> bool;
	bool isPlayerInRadius(const sf::FloatRect& observationArea, const sf::FloatRect& playerBounds, float radius);
	bool canMoveForward() const;
	bool hit_a_wall() const;
	bool canJumpForward() const;
	const FloatRect get_global_bounds_anim() const;


	//virtual
	virtual PL_SIDE getPlayerSide(float playerX, float enemyX);
	virtual void jump(const float dir_y);
	virtual void walk(const float dir_x);
	virtual void changeHP(short);
	virtual void jump_towards_player();
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
