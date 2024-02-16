#pragma once

#include "TileMap.h"
#include "kusaka.h"
#include "EyeEvil.h"
#include "WolfBoss.h"
#include "RedMutant.h"

using namespace::sf;

class Projectile{
private:
	TileMap* sandbox;

	Sprite projectile_S;

	vector<vector<Enemy*>*> enemies;

	float speed;
	Vector2f dest_pos;
	Vector2f norm_s;

	void initSprite(Vector2f init_pos, TextureManager* t_manager, int index, string name);
	void initVariables();
public:
	Projectile(Vector2f init_pos, Vector2f dest_pos, TileMap* sandbox_, const vector<vector<Enemy*>*>& enemies_, 
		TextureManager* t_manager, int index, string name);

	void update();
	bool updateCollision();
	bool updateHit();

	void render(RenderTarget& target);
};

