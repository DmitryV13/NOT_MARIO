#pragma once
#include "Enemy.h"

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
	
	ENEMY_STATE hornet_state_past;
	Clock IDLE_timer;
	Clock ATTACKING_timer;
	Clock HORNET_TAKING_DAMAGE_TIMER;

	GeneralInfo* player_info_;

	float moveX;
	float moveY;

	void init_texture() override;
	void init_sprite() override;


public:
	Clock DEATH_timer;
	ENEMY_STATE hornet_state;


	explicit hornet(TileMap& map, GeneralInfo* player_info,short);
	hornet(TileMap& map, GeneralInfo* player_info_, float, float);

	~hornet() override = default;
	void update_movement() override;
	void update_animation() override;
	void shot() override;
	bool search_for_enemies() override;
	void walk(const float dir_x) override;
	void reset_Timer();
	void changeHP(short) override;
	void update_physics() override;
	void looks();
	void direction_calculation();
	void attack() override;
	void clear_shot() override;
	void reset_attention() override;





};

