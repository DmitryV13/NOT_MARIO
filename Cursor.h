#pragma once

using sf::IntRect;

class Cursor{
private:
	sf::Texture cursor_T;
	sf::Sprite cursor_S;

	IntRect currentFrame;
public:
	Cursor();
	void initTexture();
	void initSprite();
	void update(sf::Vector2f position);
	void render(sf::RenderTarget& target);
};

