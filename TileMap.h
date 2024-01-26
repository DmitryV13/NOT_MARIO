#pragma once
#include "Tile.h"
#include "TileAnim.h"
#include "TileFactory.h"
#include "Object.h"
#include "AnimObject.h"
#include "MovingAnimObject.h"
#include "MovingObject.h"
#include "Chest.h"
#include "Switch.h"
#include "WarehouseItem.h"



class TileMap {
private:
	
	int bim = 2;
	sf::Texture background_T;
	sf::Sprite backround_S;

	Tile ****tilemap;
	std::vector<Object*> object;

	std::unordered_map<char, Tile*> tile_list;
	std::unordered_map<char, Tile*> tile_list_back;
	std::unordered_map<char, Tile*> tile_list_front;
	
	float mapW;
	float mapH;
	float sizeTexture;

	float coefficient_X;
	float coefficient_Y;

	std::stack<std::pair<float, float>> enemy_position;
	void init_pos_enemy();

	void writeFile();

	void init_background();
	void init_coeff(sf::IntRect pos);

	void init_tilemap(float mapW, float mapH);
	void init_level(short int level);

	void init_objects(short int level);
	void init_animObjects(short int level);
	void init_movingObjects(short int level);
	void init_movingAnimObjects(short int level);
	void init_switch(short int level);
	void init_chest(short int level);

	void init_tile_list();
	void init_tile_list_back();
	void init_tile_list_front();

	Tile* give_tile(char letter);
	Tile* give_tile_back(char letter);
	Tile* give_tile_front(char letter);

	void first_renderObject(sf::RenderTarget& target);

public:
	TileMap(short level);
	~TileMap();
	void free_memory();

	sf::Vector2f cord_enemy();


	float getMapWidth();
	float getMapHeight();
	float getSizeTexture();

	short getInteraction(int i, int j);
	bool isBlock(int i, int j);
	bool outOfMap(int i, int j);

	void add_tile(int i, int j, char association);
	void delete_tile(int i, int j, char association);

	void background_render(sf::RenderTarget& target, sf::FloatRect view_cords);
	void first_render(sf::RenderTarget& target, sf::FloatRect view_cords);
	void second_render(sf::RenderTarget& target, sf::FloatRect view_cords);
	void update(sf::RenderTarget& target, sf::FloatRect view_cords);

	bool isOccupied(int i, int j);
	void updatePlayerPresence(int indexI[], int indexJ[]);
	vector<Object*>& getObjects();
};

