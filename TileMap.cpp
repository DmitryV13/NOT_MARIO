#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(){
	init_texture();
	TileFactory factory;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 100; j++){
			tilemap[i][j] = factory.tile_map_inFactory[i][j];
		}
	}
}
int TileMap::init_texture(){

	if (!block_T.loadFromFile("Textures/Textures_map/earth.png")) {
		return -1;
	}
	block_S.setTexture(block_T);

}

void TileMap::render(sf::RenderTarget& target)
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 100; j++) {
			block_S.setTextureRect(tilemap[i][j].give_cord());
			block_S.setPosition(j * 73, i * 73);
			target.draw(block_S);
		}
	}
}
