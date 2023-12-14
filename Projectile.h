#pragma once

#include "TileMap.h"

using namespace::sf;

class Projectile{
private:
	TileMap* sandbox;

	Texture projectile_T;
	Sprite projectile_S;


	float speed;
	Vector2f dest_pos;
	Vector2f norm_s;

	void initTexture();
	void initSprite(Vector2f init_pos);
	void initVariables();
public:
	Projectile(Vector2f init_pos, Vector2f dest_pos, TileMap* sandbox_);

	void update();
	bool updateCollision();
	bool checkHit();

	void render(RenderTarget& target);
};

