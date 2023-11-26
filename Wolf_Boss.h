#pragma once
#include "Enemy.h"
class Wolf_Boss :
    public Enemy
{
	Texture Wolf_Boss_t_;
	bool player_l_r[2]{ false };
	int count_anger = 0;
	float moving_prev = 0;
	
	void init_texture() override;
	void init_sprite() override;


public:
	explicit Wolf_Boss(TileMap& map);
	~Wolf_Boss() override = default;
	void update_movement() override;
	void update_animation() override;
	void clear_shot() override;
	void shot() override;
	void attack() override;
	bool search_for_enemies() override;
	void reset_attention() override;
};

