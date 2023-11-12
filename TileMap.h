#pragma once
#include "Tile.h"
#include "TileFactory.h"

class TileMap {
private:

	sf::Texture block_T[2];
	sf::Sprite block_S[2];
	sf::Texture background_T;
	sf::Sprite background_S;
	Tile tilemap[40][201];
	float sizeTexture;
	float mapW;
	float mapH;
public:
	TileMap();

	float getMapWidth();
	float getMapHeight();
	float getSizeTexture();
	bool isBlock(int i, int j);

	void updatePlayerPresence(int indexI[], int indexJ[]);

	void init_texture();
	void render(sf::RenderTarget& target);


	Tile& setPosTile(int i, int j);
	bool isOccupied(int i, int j);
};

