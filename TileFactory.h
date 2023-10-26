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
	void down(std::string (*map)[200], int &i, int &j);
	void up(std::string (*map)[200], int &i, int &j);
	void directly(std::string(* map)[200], int &i, int &j);
	void zigzag(std::string(* map)[200], int &i, int &j, int area);
	void river(std::string(* map)[200], int &i, int &j);
	void afill(std::string [n][m], int &i, int &j);
};
