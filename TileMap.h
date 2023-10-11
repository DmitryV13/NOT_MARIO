#pragma once
#include "Tile.h"
#include "TileFactory.h"

class TileMap{
private:
	
	sf::Texture block_T;
	sf::Sprite block_S;
	Tile tilemap[20][100];

public:
	TileMap();
	int init_texture();
	void render(sf::RenderTarget& target);
};

