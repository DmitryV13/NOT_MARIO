#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
	:sizeTexture(60)
	, mapW(40)
	, mapH(200) {

	init_texture();
	TileFactory factory;
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 200; j++) {
			tilemap[i][j] = factory.tile_map_inFactory[i][j];
		}
	}
}

Tile& TileMap::getTile()
{
	return **tilemap;
}


Tile& TileMap::setPosTile(int i, int j)
{
	return tilemap[i][j];
}


void TileMap::init_texture() {

	if (!block_T[0].loadFromFile("Textures/Textures_map/map1.png")) {
		std::cout << "Error -> TileMap -> couldn't load texture";
	}
	//if (!block_T[1].loadFromFile("Textures/Textures_map/map_back.png")) {
	//	std::cout << "Error -> TileMap -> couldn't load texture";
	//}
	//if (!background_T.loadFromFile("Textures/Textures_map/background_test.jpg")) {
	//	std::cout << "Error -> TileMap -> couldn't load texture";
	//}
	block_S[0].setTexture(block_T[0]);
	//block_S[1].setTexture(block_T[1]);
	//background_S.setTexture(background_T);
}
	
	void TileMap::render(sf::RenderTarget& target)
	{
		//target.draw(background_S);
		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 200; j++) {
				//block_S[1].setTextureRect(tilemap[i][j].give_cord());
				//block_S[1].setPosition(j * 60, i * 60);
				//target.draw(block_S[1]);
				//std::cout << tilemap[i][j].give_player_info();
				block_S[0].setTextureRect(tilemap[i][j].give_cord());
				block_S[0].setPosition(j * 60, i * 60);
				target.draw(block_S[0]);

			}
			//std::cout << std::endl;
		}
	}

	float TileMap::getMapWidth(){
		return mapH * sizeTexture;
	}

	float TileMap::getMapHeight(){
		return mapW * sizeTexture;
	}

	float TileMap::getSizeTexture() {
		return sizeTexture;
	}

	bool TileMap::isBlock(int i, int j){
		if (tilemap[i][j].give_front_tile() != ' ')
			return true;
		return false;
	}

	bool TileMap::isOccupied(int i, int j) {
		return tilemap[i][j].give_player_info();
	}

	void TileMap::updatePlayerPresence(int indexI[], int indexJ[]) {
		for (int k = 0; k < mapW; k++){
			for (int l = 0; l < mapH; l++) {
				tilemap[k][l].setTilePresence(false);
			}
		}
		for (int i = 0; i < 6 && indexI[i]!=-1 && indexJ[i] != -1; i++){
			//std::cout << " " << indexI[i] << " " << indexJ[i] << std::endl;
			tilemap[indexI[i]][indexJ[i]].setTilePresence(true);
		}
	}
