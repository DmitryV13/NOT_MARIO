#pragma once

#include "TileMap.h"

using namespace::sf;

class Bullet{
private:
	TileMap* sandbox;

	Texture bullet_T;
	Sprite bullet_S;

	float speed;
	Vector2f dest_pos;
	Vector2f norm_s;

	void initTexture();
	void initSprite(Vector2f init_pos);
	void initVariables();
public:
	Bullet(Vector2f init_pos, Vector2f dest_pos, TileMap* sanbox);

	void update();
	bool updateCollision();

	void render(RenderTarget& target);
};

