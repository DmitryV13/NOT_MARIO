#pragma once
#include "Enemy.h"

using sf::Sprite;
using sf::RenderWindow;
using sf::FloatRect;
using sf::View;
using sf::Texture;
using sf::IntRect;
using sf::Clock;

enum class HORNET_HIVE_STATE
{
	IDLE = 0,
	DEATH,
	TAKING_DAMAGE
};


class HornetHive:public Enemy
{
private:
	Texture HornetHive_t_;

	HORNET_HIVE_STATE hornet_hive_state_past;
	Clock HORNET_TAKING_DAMAGE_TIMER;
	GeneralInfo* player_info_;


	void init_texture() override;
	void init_sprite() override;


public:
	Clock DEATH_timer;
	HORNET_HIVE_STATE hornet_state;
	short cout_hornet{ 3 };
	bool HIVE_LIFE() const;
	void set_position_AR(const float x, const float y);

	explicit HornetHive(TileMap& map, GeneralInfo* player_info,short);
	HornetHive(TileMap& map, GeneralInfo* player_info_, float pos_x, float pos_y);

	~HornetHive() override = default;
	void update_movement() override;
	void update_animation() override;
	void shot() override;
	bool search_for_enemies() override;
	void reset_Timer();
	void attack() override;
	void clear_shot() override;
	void reset_attention() override;
	void changeHP(short) override;
	void update_physics() override;



};

