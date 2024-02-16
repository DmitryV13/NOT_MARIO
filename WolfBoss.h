#pragma once
#include "Enemy.h"

class WolfBoss : public Enemy
{
	ENEMY_STATE boss_state;
	ENEMY_STATE boss_state_past;
	bool boss_state_TORMENT;
	Texture Wolf_Boss_t_;
	Clock RETREATING_timer;
	Clock Jumping_att_timer;
	Clock IDLE_timer;
	Clock BOSS_TAKING_DAMAGE_TIMER;
	Clock Shot_timer;
	Clock DEATH_timer;
	Clock att_timer;


	bool jump_flag{true};
	short count_jm;
	short count_anim{0};


	bool player_l_r[2]{false};
	//int count_anger = 0;
	int retreat_counter;
	int max_retreat_duration;
	bool awakening;
	bool pl_contact;
	bool pl_cont_jump;
	int rand_;
	float distance;


	void init_texture() override;
	void init_sprite() override;
	void init_physics() override;

public:
	explicit WolfBoss(TileMap& map, GeneralInfo* player_info,short);
	WolfBoss(TileMap& map, GeneralInfo* player_info_, float pos_x, float pos_y);

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
	void shot_HOWL();
	void reset_Timer();
	bool outside_sting() override;
	void looks();
	void changeHP(short) override;
	void updateHP_bar() override;


	sf::Vector2f calculateRandomPosition(const sf::FloatRect& playerBounds, int jumpDistance);

	ORIENTATION getPlayerSide(float playerX, float enemyX);
	void look(float direction);
	void bite();
	void reset_step();
};
