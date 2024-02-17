#pragma once
#include "Map.h"
#include "TileMap.h"
#include "laser_weapon.h"
#include "GeneralInfo.h"
#include "HealthBarEnemy.h"
#include "killer_leaf.h"
#include "ENEMY_ANIMATION_STATE.h"
#include "ORIENTATION.h"
#include "ENEMY_STATE.h"

using sf::Sprite;
using sf::RenderWindow;
using sf::FloatRect;
using sf::View;
using sf::Texture;
using sf::IntRect;
using sf::Clock;


class Enemy
{
protected:
	TextureManager* t_manager;
	TileMap* sandbox;
	GeneralInfo* player_info;

	Sprite Enemy_S;
	Sprite observation_area;
	Sprite anim_area;
	IntRect current_frame;
	IntRect current_area;
	IntRect standard_frame;
	Clock animation_timer;
	Clock blow_timer;

	HealthBarEnemy* hp_bar;

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
	virtual void init_sprite(int index, string name) = 0;

public:
	//Enemy
	bool looks_to_the_left;
	bool looks_to_the_right;
	sf::Vector2f generate_random_start_position(int mapWidth, int mapHeight);
	Enemy(TileMap& map, GeneralInfo* player_info_, short, TextureManager* t_manager_);
	Enemy(TileMap& map, GeneralInfo* player_info_, float, float, TextureManager* t_manager_);
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
	short getHP();
	virtual void updateHP_bar() ;

	//virtual
	virtual bool outside_sting();

	virtual ORIENTATION getPlayerSide(float playerX, float enemyX);
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
