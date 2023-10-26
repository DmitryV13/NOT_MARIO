#pragma once
#include "Tile.h"
#include "TileFactory.h"

class TileMap {
private:

	sf::Texture block_T;
	sf::Sprite block_S;
	Tile tilemap[40][200];
	float sizeTexture;
	float mapW;
	float mapH;
public:
	TileMap();
	Tile& getTile();
	Tile& setPosTile(int i, int j);
	float getMapWidth();
	float getMapHeight();
	float getSizeTexture();
	bool isBlock(int i, int j);

	void init_texture();
	void render(sf::RenderTarget& target);
};

