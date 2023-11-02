#pragma once
#include "Enemy.h"

class EvilBall:public Enemy
{
public:
	explicit EvilBall(TileMap& map);
	~EvilBall() override = default;

private:

	Texture EvilBall_T;
	void init_texture() override;
	void init_sprite() override;
	
};

