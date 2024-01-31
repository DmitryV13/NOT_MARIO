#pragma once
#include "Enemy.h"
#include "BOSS_STATE.h"



class WolfBoss : public Enemy
{
	BOSS_STATE boss_state_;
	BOSS_STATE boss_state_past_;

	Texture wolf_boss_t_;

	Clock retreating_timer_;
	Clock jumping_att_timer_;
	Clock idle_timer_;
	Clock boss_taking_damage_timer_;
	Clock shot_timer_;
	Clock death_timer_;
	Clock att_timer_;

	GeneralInfo* player_info_;

	bool jump_flag_{true};
	bool boss_state_torment_;
	bool player_l_r_[2]{ false };
	bool awakening_;
	bool pl_contact_;
	bool pl_cont_jump_;

	short count_jm;
	short count_anim{0};

	int retreat_counter_;
	int max_retreat_duration_;
	int rand_;

	float distance_;

	void init_texture() override;
	void init_sprite() override;
	void init_physics() override;

public:
	explicit WolfBoss(TileMap& map, GeneralInfo* player_info,short);
	WolfBoss(TileMap& map, GeneralInfo* player_info_, float pos_x, float pos_y);
	sf::Vector2f calculate_random_position(int jump_distance) const;
	PL_SIDE getPlayerSide(float player_x, float enemy_x) override;

	void look(float direction);
	void bite();
	void reset_step();
	void reset_Timer();
	void looks();
	void shot_howl() const;

	~WolfBoss() override = default;
	void update_movement() override;
	void update_animation() override;
	void clear_shot() override;
	void shot() override;
	void attack() override;
	bool search_for_enemies() override;
	void reset_attention() override;
	void walk(const float dir_x) override;
	void update_physics() override;
	void jump(const float dir_y) override;
	bool outside_sting() override;
	void changeHP(short) override;
	void updateHP_bar() override;

};
