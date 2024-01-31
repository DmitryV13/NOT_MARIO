#pragma once
#include "Map.h"
#include "TileMap.h"
#include "GeneralInfo.h"
#include "LASER_ANIMATION_STATES.h"

using sf::Sprite;
using sf::RenderWindow;
using sf::FloatRect;
using sf::View;
using sf::Texture;
using sf::IntRect;
using sf::Clock;
using sf::Vector2f;



class laser_weapon
{
protected:
	TileMap* sandbox;

	Texture laser_T;

	Sprite laser_S;
	Sprite laser_area;

	IntRect current_frame;

	Clock animation_timer;
	Clock laser_timer;

	short attack;
	short animation_state;
	short cout_las{ 0 };

	bool animation_switch;
	bool dir_x;

	int first;
	int next;

	GeneralInfo* player_info;

	void init_texture();
	void init_sprite();
	void init_variables(int);
	void init_animation();
	void init_physics();

public:
	explicit laser_weapon(TileMap& map, int, float, float, bool, GeneralInfo* player_info_);
	~laser_weapon() = default;

	const bool& get_animation_switch();
	sf::Vector2f get_position() const;
	const FloatRect get_global_bounds() const;
	void set_position(const float x, const float y);
	void render(sf::RenderTarget& target);
	void render_fl(sf::RenderTarget& target);
	void update();
	void update_animation();
	void reset_animation_timer();
	sf::Vector2f calculate_end_position(float x) const;
	bool collision_block(int, int) const;
	bool update_collision_x();
	void damage(sf::Vector2f, sf::Vector2f);
	bool hit_a_wall(const sf::Vector2f& current_position, float x) const;
};
