#pragma once
#include "common/Global.hpp"

#include "map/TileMap.h"
#include "units/enemies/kusaka.h"
#include "units/enemies/EyeEvil.h"
#include "units/enemies/WolfBoss.h"
#include "units/enemies/RedMutant.h"

using namespace::sf;

class Projectile{
private:
	TileMap* sandbox;

	Texture projectile_T;
	Sprite projectile_S{ Global::dummyTexture };

	vector<vector<Enemy*>*> enemies;

	float speed;
	Vector2f dest_pos;
	Vector2f norm_s;

	void initTexture();
	void initSprite(Vector2f init_pos);
	void initVariables();
public:
	Projectile(Vector2f init_pos, Vector2f dest_pos, TileMap* sandbox_, const vector<vector<Enemy*>*>& enemies_);

	void update();
	bool updateCollision();
	bool updateHit();

	void render(RenderTarget& target);
};

