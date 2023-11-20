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
	void map_generation(char [n][m]);
	void flatland(char(*map)[200], int& i, int& j, int shift, std::mt19937 gen);
	void mountainous_terrain(char(*map)[200], int& i, int& j, int& shift, std::mt19937 gen);
	void water_bodies(char(*map)[200], int& i, int& j, int shift, std::mt19937 gen);
	void tunnel(char(*map)[200], int& i, int& j, int shift, std::mt19937 gen);
	void wormhole(char(*map)[200], int& i, int& j, int shift, std::mt19937 gen);
	void cavern(char(*map)[200], int& i, int& j, int shift, std::mt19937 gen);
	void start_of_map_generation_(char[n][m], int& i, int& j, std::mt19937 gen);
	void filter_map(char map[n][m]);
	int count_empty_neighbors(char map[n][m], int i, int j);
	void filter_map1(char map[n][m]);
	bool has_blocks_on_both_sides(char map[n][m], int i, int j);
	void artist_method(char map[n][m]);
	void fill_lakes_with_ground(char map[n][m]);
};
