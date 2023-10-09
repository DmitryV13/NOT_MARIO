#pragma once
class Tile
{
private:
	sf::Texture tile_T;
	sf::Sprite tile_S;
	sf::IntRect currentFrame;
	int interaction;
public:
	Tile(std::string path_T, sf::IntRect textureRect, int interaction);
	
	void initTexture(std::string path_T);
	void initSprite();

	// Accessors
	const sf::Vector2f getPosition() const;

	// Modifiers
	void setPosition(const float x, const float y);
	
	void update();
	void render(sf::RenderTarget& target);
};

