#pragma once
#include "Enemy.h"
enum class Boss_STATE { SLEEP, IDLE, MOVING, JUMPING, ATTACKING, RETREATING };

enum class PL_Side
{
	LEFT,
	RIGHT
};

class Wolf_Boss :
	public Enemy
{
	Boss_STATE boss_state;
	Texture Wolf_Boss_t_;
	bool player_l_r[2]{false};
	int count_anger = 0;
	int retreat_counter;
	int max_retreat_duration;
	bool awakening;
	bool pl_contact;
	


	void init_texture() override;
	void init_sprite() override;
	void init_physics() override;

public:
	explicit Wolf_Boss(TileMap& map, Player&);
	~Wolf_Boss() override = default;
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

	PL_Side getPlayerSide(float playerX, float enemyX);
	void look(float direction);
};
