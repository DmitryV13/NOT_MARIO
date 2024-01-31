#pragma once
#include "Enemy.h"
#include "HORNET_STATE.h"


using sf::Sprite;
using sf::RenderWindow;
using sf::FloatRect;
using sf::View;
using sf::Texture;
using sf::IntRect;
using sf::Clock;

class hornet:public Enemy
{
private:
	Texture hornet_t_;
	
	HORNET_STATE hornet_state_past_;

	Clock idle_timer_;
	Clock attacking_timer_;
	Clock hornet_taking_damage_timer_;

	GeneralInfo* player_info_;

	float move_x_;
	float move_y_;

	void init_texture() override;
	void init_sprite() override;

public:
	Clock death_timer;
	HORNET_STATE hornet_state;


	explicit hornet(TileMap& map, GeneralInfo* player_info,short);
	hornet(TileMap& map, GeneralInfo* player_info_, float, float);

	void reset_Timer();
	void looks();
	void direction_calculation();


	~hornet() override = default;
	void update_movement() override;
	void update_animation() override;
	void shot() override;
	bool search_for_enemies() override;
	void walk(const float dir_x) override;
	void changeHP(short) override;
	void update_physics() override;
	void attack() override;
	void clear_shot() override;
	void reset_attention() override;





};

