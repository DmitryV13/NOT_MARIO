#pragma once
#include "Tile.h"

class TileFactory{
private:
	std::unordered_map<std::string, Tile>  blocks;
	void initBlocks();
public:
	TileFactory();
	//Tile getBlock(std::string blockName);
};

