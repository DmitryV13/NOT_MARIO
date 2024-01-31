#pragma once
#include "Enemy.h"
#include "KUSAKA_STATE.h"


class kusaka : public Enemy
{
public:
	KUSAKA_STATE kusaka_state;
	KUSAKA_STATE kusaka_state_past;

	Clock idle_timer;
	Clock death_timer;
	Clock kusaka_taking_damage_timer;

	bool jump_flag{true};

	short count_jm;
	GeneralInfo* player_info_;

	explicit kusaka(TileMap& map, GeneralInfo* player_info,short);
	kusaka(TileMap& map, GeneralInfo* player_info_, float pos_x, float pos_y);

	void reset_timer();
	bool update_collision_move_x();

	~kusaka() override = default;
	void update_movement() override;
	void update_animation() override;
	void clear_shot() override;
	void shot() override;
	void attack() override;
	bool search_for_enemies() override;
	void reset_attention() override;
	void walk(const float dir_x) override;

private:
	Texture kusaka_t_;
	bool player_l_r_[2]{false};
	int count_jump_ = 0;

	void init_texture() override;
	void init_sprite() override;
};
