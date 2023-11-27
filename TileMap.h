#pragma once
#include "Tile.h"
#include "TileBox.h"
#include "TileAnim.h"
#include "TileFactory.h"
#include <vector>


class TileMap {
private:

	sf::Texture background_T;
	sf::Sprite backround_S;

	std::vector <std::vector<Tile*>> generation_tilemap;
	std::vector<std::vector<std::vector<Tile*>>> tilemap;

	std::unordered_map<char, Tile*> tile_list;
	std::unordered_map<char, Tile*> tile_list_back;
	std::unordered_map<char, Tile*> tile_list_front;
	
	float sizeTexture;
	float mapW;
	float mapH;

	float coefficient_X = 1;
	float coefficient_Y = 1;

	void init_background();

	void init_generation_tilemap(float mapW, float mapH);
	void init_tilemap(float mapW, float mapH);
	
	void init_tile_list();
	void init_tile_list_back();
	void init_tile_list_front();

	Tile* give_tile(char letter);
	Tile* give_tile_back(char letter);
	Tile* give_tile_front(char letter);
	Tile* init_tile_box(char letter);

public:
	TileMap();

	float getMapWidth();
	float getMapHeight();
	float getSizeTexture();
	bool isBlock(int i, int j);

	void add_tile(int i, int j, char association);
	void delete_tile(int i, int j, char association);

	void background_render(sf::RenderTarget& target, sf::FloatRect view_cords);
	void first_render(sf::RenderTarget& target, sf::FloatRect view_cords);
	void second_render(sf::RenderTarget& target, sf::FloatRect view_cords);
	void update(sf::RenderTarget& target, sf::FloatRect view_cords);
};

