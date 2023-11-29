#pragma once

#include "PLAYER_ANIMATION_SATES.h"
#include "TileMap.h"

using namespace::sf;

class Arrow{
private:
	TileMap* sandbox;

	Texture arrow_T;
	Sprite arrow_S;

	short side;
	bool is_flying;
	float speed;
	Vector2f dest_pos;
	Vector2f norm_s;

	void initTexture();
	void initSprite(Vector2f init_pos);
	void initVariables();
public:
	Arrow(Vector2f init_pos, short side, TileMap* sanbox_);

	void update();
	bool updateCollision();

	void letOff(Vector2f dest_pos_);
	void setPosition(Vector2f position);
	void setRotationAngle(float angle);
	const bool isFlying() const;

	void render(RenderTarget& target);
};

