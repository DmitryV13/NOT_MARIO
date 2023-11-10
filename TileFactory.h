#pragma once
#include <random>

#include "Tile.h"


class TileFactory
{
private:
	sf::IntRect initRect_tile(char tile);

public:

	TileFactory();
	static const int n = 40;
	static const int m = 200;
	Tile tile_map_inFactory[n][m];
	bool getPosPlayer(int, int);
	void map_generation(std::string[n][m]);
	void flatland(std::string(*map)[200], int& i, int& j, int shift, std::mt19937 gen);
	void mountainous_terrain(std::string(*map)[200], int& i, int& j, int& shift, std::mt19937 gen);
	void water_bodies(std::string(*map)[200], int& i, int& j, int shift, std::mt19937 gen);
	void tunnel(std::string(*map)[200], int& i, int& j, int shift, std::mt19937 gen);
	void wormhole(std::string(*map)[200], int& i, int& j, int shift, std::mt19937 gen);
	void cavern(std::string(*map)[200], int& i, int& j, int shift, std::mt19937 gen);
	
	void start_of_map_generation_(std::string[n][m], int& i, int& j, std::mt19937 gen);
	void filter_map(std::string map[n][m]);
	int count_empty_neighbors(std::string map[n][m], int i, int j);
	void filter_map1(std::string map[n][m]);
	bool has_blocks_on_both_sides(std::string map[n][m], int i, int j);
	void artist_method(std::string map[n][m]);
	void fill_lakes_with_ground(std::string map[n][m]);
};
