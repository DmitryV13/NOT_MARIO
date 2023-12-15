#pragma once

#include "PLAYER_ANIMATION_SATES.h"
#include "Weapon.h"
#include "Arrow.h"
#include "TileMap.h"
#include "kusaka.h"
#include "Eye_evil.h"
#include "WolfBoss.h"
#include "RedMutant.h"

using namespace::sf;

class Bow : public Weapon{
private:
	TileMap* sandbox;

	Texture bow_T;
	Sprite bow_S;


	vector<Eye_evil*>* e;
	vector<kusaka*>* k;
	vector<RedMutant*>* r;
	vector<WolfBoss*>* w;

	IntRect currentFrame;
	Clock animationTimer;

	vector<Arrow*> arrows;
	Vector2f arrow_dir;


	bool bow_pulled;
	float rot_angle;
	short animationState;
	bool animationSwitch;
	bool attack_activation;
	short side_of_attack;
	short previous_side;

	void initTexture();
	void initSprite(Vector2f player_position, FloatRect player_bounds);
	void initVariables();
	void initAnimation();

public:
	Bow(Vector2f player_position, FloatRect player_bounds, TileMap* sandbox_, vector<kusaka*>* k, vector<Eye_evil*>* e, vector<RedMutant*>* r, vector<WolfBoss*>* w);

	void update(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords) override;
	void updatePosition(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords);
	void updateArrowPosition();
	void updateAnimation();
	void updateProjectiles();

	void render(RenderTarget& target) override;
	void renderProjectiles(RenderTarget& target) override;

	void attack(short side_attack, Vector2f mouse_pos, FloatRect view_cords, bool is_btn_pressed) override;
};

