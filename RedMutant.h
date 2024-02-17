#pragma once
#include "Enemy.h"

class RedMutant : public Enemy
{
private:
	Clock IDLE_timer;

	Clock RED_MUTANT_TAKING_DAMAGE_TIMER;
	Clock Shot_timer;
	bool teleport{true};
	bool jump_flag{true};
	short count_jm;
	short count_anim{0};
	bool player_l_r[2]{false};
	int count_jump = 0;
	int count_atack = 0;
	void init_sprite(int index, string name) override;

public:
	ENEMY_STATE red_mutant_state;
	ENEMY_STATE red_mutant_state_past;
	Clock DEATH_timer;
	sf::Vector2f calculateRandomPosition(const sf::FloatRect& playerBounds, int radius);
	explicit RedMutant(TileMap& map, GeneralInfo* player_info, short, TextureManager* t_manager, int index, 
		string name);
	RedMutant(TileMap& map, GeneralInfo* player_info_, float pos_x, float pos_y, TextureManager* t_manager, 
		int index, string name);

	~RedMutant() override = default;
	void reset_Timer();
	void walk(const float dir_x) override;
	void update_movement() override;
	void update_animation() override;
	void clear_shot() override;
	void shot() override;
	void attack() override;
	bool search_for_enemies() override;
	void reset_attention() override;
	void changeHP(short) override;
	void updateHP_bar() override;

	bool plStan();
};
