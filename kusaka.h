#pragma once
#include "Enemy.h"

class kusaka : public Enemy
{
public:
	explicit kusaka(TileMap& map);
	~kusaka() override = default;
	void update_movement() override;
	void update_animation() override;
	void clear_shot() override;
	void shot() override;
	void attack() override;
	bool search_for_enemies() override;
	void reset_attention() override;
	

private:
	Texture kusaka_t_;
	bool player_l_r[2]{false};
	int count_jump = 0;
	void init_texture() override;
	void init_sprite() override;
};
