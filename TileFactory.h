#pragma once
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
	void map_generation(std::string [n][m]);
	void flatland(std::string(* map)[200], int &i, int& j, int shift, std::mt19937 gen);
	void mountainous_terrain(std::string(* map)[200], int& i, int& j, int& shift, std::mt19937 gen);
	void water_bodies(std::string(* map)[200], int& i, int& j, int shift, std::mt19937 gen);
	void tunnel(std::string(* map)[200], int& i, int& j, int shift, std::mt19937 gen);
	void wormhole(std::string(* map)[200], int& i, int& j, int shift, std::mt19937 gen);
	void cavern(std::string(* map)[200], int& i, int& j, int shift, std::mt19937 gen);
	void soaring_islands(std::string(* map)[200], int& i, int& j, int shift, std::mt19937 gen);
	void afill(std::string [n][m], int &i, int &j, std::mt19937 gen);
	void filterMap(std::string map[n][m]);
	int countEmptyNeighbors(std::string map[n][m], int i, int j);
};
