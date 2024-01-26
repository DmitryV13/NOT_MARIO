#pragma once

#include "PLAYER_ANIMATION_SATES.h"
#include "Weapon.h"
#include "Projectile.h"
#include "kusaka.h"
#include "EyeEvil.h"
#include "WolfBoss.h"
#include "RedMutant.h"
#include "GeneralInfo.h"

using namespace::sf;

class CombatStaff : public Weapon{
private:
	GeneralInfo* p_info;
	TileMap* sandbox;

	Texture staff_T;
	Sprite staff_S;

	vector<vector<Enemy*>*> enemies;

	IntRect currentFrame;
	Clock animationTimer;

	vector<Projectile*> projectiles;


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
	CombatStaff(Vector2f player_position, FloatRect player_bounds, TileMap* sandbox_,
		const vector<vector<Enemy*>*>& enemies_, GeneralInfo* p_info_);

	void update(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords) override;
	void updatePosition(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords);
	void updateAnimation();
	void updateProjectiles();

	void render(RenderTarget& target) override;
	void renderProjectiles(RenderTarget& target) override;

	void attack(short side_attack, Vector2f mouse_pos, FloatRect view_cords, bool is_btn_pressed) override;
};

