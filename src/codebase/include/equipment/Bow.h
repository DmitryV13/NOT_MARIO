#pragma once
#include "common/Global.hpp"

#include "units/player/enums/PLAYER_ANIMATION_SATES.h"
#include "equipment/Weapon.h"
#include "equipment/Arrow.h"
#include "map/TileMap.h"
#include "units/enemies/kusaka.h"
#include "units/enemies/EyeEvil.h"
#include "units/enemies/WolfBoss.h"
#include "units/enemies/RedMutant.h"

using namespace::sf;

class Bow : public Weapon{
private:
	TileMap* sandbox;

	Texture bow_T;
	Sprite bow_S{ Global::dummyTexture };

	vector<vector<Enemy*>*> enemies;

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
	Bow(Vector2f player_position, FloatRect player_bounds, TileMap* sandbox_, const vector<vector<Enemy*>*>& enemies_);

	void update(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords) override;
	void updatePosition(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords);
	void updateArrowPosition();
	void updateAnimation();
	void updateProjectiles();

	void render(RenderTarget& target) override;
	void renderProjectiles(RenderTarget& target) override;

	void attack(short side_attack, Vector2f mouse_pos, FloatRect view_cords, bool is_btn_pressed) override;
};

