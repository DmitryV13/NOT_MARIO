#pragma once

using namespace::sf;

class Sword {
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

	void render(RenderTarget& target);

	void updatePosition(Vector2f player_position, short player_side);
	void updateAnimation();

	void attack(short side_attack);
};