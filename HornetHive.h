#pragma once
#include "Enemy.h"
#include "HORNET_HIVE_STATE.h"

using sf::Sprite;
using sf::RenderWindow;
using sf::FloatRect;
using sf::View;
using sf::Texture;
using sf::IntRect;
using sf::Clock;




class HornetHive:public Enemy
{
private:
	Texture HornetHive_t_;

	HORNET_HIVE_STATE hornet_hive_state_past_;

	Clock hornet_taking_damage_timer_;

	GeneralInfo* player_info_;


	void init_texture() override;
	void init_sprite() override;


public:
	Clock death_timer;

	HORNET_HIVE_STATE hornet_state;

	short cout_hornet{ 3 };


	explicit HornetHive(TileMap& map, GeneralInfo* player_info,short);
	HornetHive(TileMap& map, GeneralInfo* player_info_, float pos_x, float pos_y);

	bool hive_life() const;
	void set_position_ar(const float x, const float y);
	void reset_timer();

	~HornetHive() override = default;
	void update_movement() override;
	void update_animation() override;
	void shot() override;
	bool search_for_enemies() override;
	void attack() override;
	void clear_shot() override;
	void reset_attention() override;
	void changeHP(short) override;
	void update_physics() override;



};

