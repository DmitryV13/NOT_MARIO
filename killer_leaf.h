#pragma once

#include "Map.h"
#include "TileMap.h"
#include "GeneralInfo.h"

using sf::Sprite;
using sf::RenderWindow;
using sf::FloatRect;
using sf::View;
using sf::Texture;
using sf::IntRect;
using sf::Clock;
using sf::Vector2f;

class killer_leaf
{

protected:
	TileMap* sandbox;
	short attack;
	Sprite leaf_S;
	IntRect current_frame;
	Clock animation_timer;
	bool animation_switch;
	GeneralInfo* player_info;
	vector<float> flight_cord_;
	float moveX;
	float moveY;
	sf::Vector2f displacement;
	bool extermination_flag;

	void init_sprite(TextureManager* t_manager, int index, string name);
	void init_animation();

public:
	explicit killer_leaf(TileMap& map, vector<float>flightCord
	, GeneralInfo* player_info_, TextureManager* t_manager, int index, string name);
	~killer_leaf() = default;

	sf::Vector2f get_position() const;
	const FloatRect get_global_bounds() const;
	void set_position(const float x, const float y);
	void render(sf::RenderTarget& target);
	void update();
	void update_animation();
	void reset_animation_timer();
	bool update_collision_x();
	bool update_collision_y();
	void damage();
	void calculation_formula();
	bool leaf_existence();
};

