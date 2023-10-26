#include "stdafx.h"
#include "TileMap.h"

	TileMap::TileMap()
		:sizeTexture(60)
		,mapW(40)
		,mapH(200) {

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
	
		if (!block_T.loadFromFile("Textures/Textures_map/map.png")) {
			std::cout << "Error -> TileMap -> couldn't load texture";
		}
		block_S.setTexture(block_T);
	}
	
	void TileMap::render(sf::RenderTarget& target)
	{
		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 200; j++) {
				block_S.setTextureRect(tilemap[i][j].give_cord());
				block_S.setPosition(j * 60, i * 60);
				target.draw(block_S);
			}
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
