#pragma once
#include "Enemy.h"

class Eye_evil :public Enemy
{
public:
	explicit Eye_evil(TileMap& map);
	~Eye_evil() override = default;

private:

	Texture evil_ball_t_;
	void init_texture() override;
	void init_sprite() override;

};

