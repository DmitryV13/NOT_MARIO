#include "stdafx.h"
#include "TileFactory.h"

void TileFactory::initBlocks(){
	Tile granite("...path...", sf::IntRect(0, 0, 20, 20), 0);
	Tile earth("...path...", sf::IntRect(0, 0, 20, 20), 1);
	Tile water("...path...", sf::IntRect(0, 0, 20, 20), 2);
	Tile bush("...path...", sf::IntRect(0, 0, 20, 20), 2);
	Tile ladder("...path...", sf::IntRect(0, 0, 20, 20), 3);
	
	blocks.insert({ "granite", granite });
	blocks.insert({ "earth", earth });
	blocks.insert({ "water", water });
	blocks.insert({ "bush", bush });
	blocks.insert({ "ladder", ladder });
}

TileFactory::TileFactory(){
	initBlocks();
}

//Tile TileFactory::getBlock(std::string blockName){
	//auto blockIterator = blocks.find(blockName);
	//if (blockIterator != blocks.end()) {
	//
	//}
//}
