#pragma once

using sf::Sprite;
using sf::Texture;
using sf::IntRect;
using sf::Clock;
using sf::RenderTarget;

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
public:
	Sword(sf::Vector2f player_position, sf::FloatRect player_bounds);

	void initTexture();
	void initSprite(sf::Vector2f player_position, sf::FloatRect player_bounds);
	void initVariables();
	void initAnimation();

	void render(RenderTarget& target);

	void updatePosition(sf::Vector2f player_position, short player_side);
	void updateAnimation();

	void attack(short side_attack);
};