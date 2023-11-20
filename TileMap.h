#pragma once
#include "Tile.h"
#include "TileFactory.h"
#include <vector>


class TileMap {
private:
	sf::Texture block_T[2];
	sf::Sprite block_S[2];
	std::vector<std::vector<Tile>> tilemap;
	std::unordered_map<char, sf::IntRect> initRectFrontMap;
	std::unordered_map<char, sf::IntRect> initRectBackMap;
	float sizeTexture;
	float mapW;
	float mapH;

	void init_texture();
	void front_record_coordinates();
	void back_record_coordinates();
	sf::IntRect initRect_tile_front(char tile);
	sf::IntRect initRect_tile_back(char tile);
public:
	TileMap();

	float getMapWidth();
	float getMapHeight();
	float getSizeTexture();
	bool isBlock(int i, int j);

	void add_tile(char letter,short int interaction, int i, int j);
	void delete_tile(char letter, short int interaction, int i, int j);
	void render(sf::RenderTarget& target);
	void second_render(sf::RenderTarget& target);
};

