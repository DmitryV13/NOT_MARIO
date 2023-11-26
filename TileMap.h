#pragma once
#include "Tile.h"
#include "TileBox.h"
#include "TileAnim.h"
#include "TileFactory.h"
#include <vector>


class TileMap {
private:

	std::vector<std::vector<Tile*>> tilemap;
	std::unordered_map<char, Tile*> tile_list;
	std::unordered_map<char, Tile*> tile_list_back;
	
	float sizeTexture;
	float mapW;
	float mapH;
	
	void init_tile_list();
	void init_tile_list_back();
	Tile* give_tile(char letter);

public:
	TileMap();

	float getMapWidth();
	float getMapHeight();
	float getSizeTexture();
	bool isBlock(int i, int j);

	void add_tile(int i, int j, char association);
	void delete_tile(int i, int j, char association);

	void first_render(sf::RenderTarget& target, sf::FloatRect view_cords);
	void second_render(sf::RenderTarget& target, sf::FloatRect view_cords);
	void update(sf::RenderTarget& target, sf::FloatRect view_cords);
};

