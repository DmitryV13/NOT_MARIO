#pragma once

#include "Map.h"
#include "TileMap.h"
#include "laser_weapon.h"
#include "GeneralInfo.h"
#include "HealthBarEnemy.h"
#include "killer_leaf.h"
#include "ENEMY_ANIMATION_STATES.h"
#include "PL_SIDE.h"

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

	HealthBarEnemy* hp_bar;

	short animation_state;
	short animation_state_past;
	short hp_damage_i;
	short HP;
	short attack_;
	short count_shot;

	bool animation_switch;
	bool jump_tile;
	bool on_ground;


	sf::Vector2f start_position;
	sf::Vector2f displacement;


	int step_left;
	int step_right;
	int attention_counter;
	int max_step{1000};
	int animation_counter_think;


	float moving;
	float displacement_max;
	float displacement_min;
	float acceleration;
	float deceleration;
	float gravity;
	float velocity_max_y;
	float jump_velocity;


	void init_animation();
	void init_variables();
	void set_at(short at);
	void set_hp(short hp);


	virtual void init_physics();
	virtual void init_texture() = 0;
	virtual void init_sprite() = 0;

public:
	bool looks_to_the_left;
	bool looks_to_the_right;

	sf::Vector2f generate_random_start_position(int map_width, int map_height) const;
	Enemy(TileMap& map, GeneralInfo* player_info_,short);
	Enemy(TileMap& map, GeneralInfo* player_info_, float,float);

	const bool& get_animation_switch();
	sf::Vector2f get_position() const;
	const FloatRect get_global_bounds() const;
	void set_position(const float x, const float y);
	void reset_jump_access();
	void render(sf::RenderTarget& target) const;
	void update();
	bool update_collision_x();
	bool update_collision_x_jump();
	bool update_collision_y();
	void reset_animation_timer();
	bool player_contact() const;
	auto sting() const -> bool;
	bool is_player_in_radius(const sf::FloatRect& observationArea, const sf::FloatRect& playerBounds, float radius) const;
	bool can_move_forward() const;
	bool hit_a_wall() const;
	bool can_jump_forward() const;
	const FloatRect get_global_bounds_anim() const;
	short getHP() const;


	virtual ~Enemy() = default;
	virtual void updateHP_bar() ;
	virtual bool outside_sting();
	virtual PL_SIDE getPlayerSide(float playerX, float enemyX);
	virtual void jump(const float dir_y);
	virtual void walk(const float dir_x);
	virtual void changeHP(short);
	virtual void jump_towards_player();
	virtual void reset_attention() = 0;
	virtual void shot() = 0;
	virtual void clear_shot() = 0;
	virtual void attack() = 0;
	virtual bool search_for_enemies() = 0;
	virtual void update_physics();
	virtual void update_movement() = 0;
	virtual void update_animation() = 0;
};
