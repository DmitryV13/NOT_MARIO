#pragma once
#include <random>

#include "Tile.h"


class TileFactory
{
private:
	sf::IntRect initRect_tile(char tile);

public:

	TileFactory(int,int);
	const int n = 40;
	const int m = 200;
	Tile tile_map_inFactory[40][200];
	bool getPosPlayer(int, int);
	void map_generation(vector<vector<char>>&);
	void flatland(vector<vector<char>>&, int& i, int& j, int shift, std::mt19937 gen);
	void mountainous_terrain(vector<vector<char>>&, int& i, int& j, int& shift, std::mt19937 gen);
	void water_bodies(vector<vector<char>>&, int& i, int& j, int shift, std::mt19937 gen);
	void tunnel(vector<vector<char>>&, int& i, int& j, int shift, std::mt19937 gen);
	void wormhole(vector<vector<char>>&, int& i, int& j, int shift, std::mt19937 gen);
	void cavern(vector<vector<char>>&, int& i, int& j, int shift, std::mt19937 gen);
	void start_of_map_generation_(vector<vector<char>>&, int& i, int& j, std::mt19937 gen);
	void filter_map(vector<vector<char>>&);
	int count_empty_neighbors(vector<vector<char>>&, int i, int j);
	void filter_map1(vector<vector<char>>&);
	bool has_blocks_on_both_sides(vector<vector<char>>&, int i, int j);
	void artist_method(vector<vector<char>>&);
	void fill_lakes_with_ground(vector<vector<char>>&);
};
