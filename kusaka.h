#pragma once
#include "Enemy.h"

class kusaka : public Enemy
{
public:
	ENEMY_STATE kusaka_state;
	ENEMY_STATE kusaka_state_past;

	Clock IDLE_timer;
	Clock DEATH_timer;
	Clock KUSAKA_TAKING_DAMAGE_TIMER;

	bool jump_flag{true};
	short count_jm;

	explicit kusaka(TileMap& map, GeneralInfo* player_info, short, TextureManager* t_manager, int index, string name);
	kusaka(TileMap& map, GeneralInfo* player_info_, float pos_x, float pos_y, TextureManager* t_manager, int index, 
		string name);

	~kusaka() override = default;
	void update_movement() override;
	void update_animation() override;
	void clear_shot() override;
	void shot() override;
	void attack() override;
	bool search_for_enemies() override;
	void reset_attention() override;
	void walk(const float dir_x) override;
	void reset_Timer();
	bool update_collision_move_x();

private:
	bool player_l_r[2]{false};
	int count_jump = 0;
	void init_sprite(int index, string name) override;
};
