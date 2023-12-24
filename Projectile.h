#pragma once

#include "TileMap.h"
#include "kusaka.h"
#include "Eye_evil.h"
#include "WolfBoss.h"
#include "RedMutant.h"

using namespace::sf;

class Projectile{
private:
	TileMap* sandbox;

	Texture projectile_T;
	Sprite projectile_S;

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

