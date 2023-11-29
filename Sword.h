#pragma once
#include "PLAYER_ANIMATION_SATES.h"
#include "Weapon.h"

using namespace::sf;

class Sword : public Weapon{
private:
	Texture sword_T;
	Sprite sword_S;
	IntRect currentFrame;
	Clock animationTimer;
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
	Sword(Vector2f player_position, FloatRect player_bounds);

	void update(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords) override;
	void updatePosition(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords);
	void updateAnimation();

	void render(RenderTarget& target) override;

	void attack(short side_attack, Vector2f mouse_pos, FloatRect view_cord, bool is_btn_pressed) override;
};