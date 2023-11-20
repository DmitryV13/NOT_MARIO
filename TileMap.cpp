#include "stdafx.h"
#include "TileMap.h"


	TileMap::TileMap() : sizeTexture(64), mapW(40), mapH(200), tilemap(41, std::vector<Tile>(201))
	{
		init_texture();
		front_record_coordinates();
		back_record_coordinates();

		TileFactory factory(mapW, mapH);
		char tileType;

		for (int i = 0; i < mapW; i++)
		{
			for (int j = 0; j < mapH; j++)
			{
				tileType = factory.generation_template[i][j];
				if (tileType == 'W' || tileType == 'w') {
					tilemap[i][j] = Tile(initRect_tile_front(tileType), tileType, tileType, 0, 64, 3);
					continue;
				}
				tilemap[i][j] = Tile(initRect_tile_front(tileType), tileType, tileType, 0, 0, 0);
			}
		}
	}

	void TileMap::front_record_coordinates()
	{
		initRectFrontMap['A'] = sf::IntRect(64, 0, sizeTexture, sizeTexture);
		initRectFrontMap['B'] = sf::IntRect(0, 0, sizeTexture, sizeTexture);
		initRectFrontMap['C'] = sf::IntRect(128, 0, sizeTexture, sizeTexture);
		initRectFrontMap['D'] = sf::IntRect(192, 0, sizeTexture, sizeTexture);
		initRectFrontMap['L'] = sf::IntRect(256, 0, sizeTexture, sizeTexture);
		initRectFrontMap['P'] = sf::IntRect(320, 0, sizeTexture, sizeTexture);
		initRectFrontMap['G'] = sf::IntRect(512, 0, sizeTexture, sizeTexture);
		initRectFrontMap['W'] = sf::IntRect(0, 64, sizeTexture, sizeTexture);
		initRectFrontMap['w'] = sf::IntRect(0, 128, sizeTexture, sizeTexture);
		initRectFrontMap['M'] = sf::IntRect(0, 192, sizeTexture, sizeTexture);
	}

	void TileMap::back_record_coordinates()
	{
		initRectBackMap['A'] = sf::IntRect(0, 0, 0, 0);
		initRectBackMap['B'] = sf::IntRect(0, 0, 0, 0);
		initRectBackMap['C'] = sf::IntRect(0, 0, 0, 0);
		initRectBackMap['D'] = sf::IntRect(0, 0, 0, 0);
		initRectBackMap['L'] = sf::IntRect(0, 0, 0, 0);
		initRectBackMap['P'] = sf::IntRect(0, 0, 0, 0);
		initRectBackMap['G'] = sf::IntRect(0, 0, 0, 0);
		initRectBackMap['W'] = sf::IntRect(256, 64, sizeTexture, sizeTexture);
		initRectBackMap['w'] = sf::IntRect(256, 128, sizeTexture, sizeTexture);
		initRectBackMap['M'] = sf::IntRect(0, 0, 0, 0);
	}

	sf::IntRect TileMap::initRect_tile_front(char tile)
	{
		auto it = initRectFrontMap.find(tile);
		if (it != initRectFrontMap.end())
		{
			return it->second;
		}
		return sf::IntRect(0, 0, 0, 0);
	}

	sf::IntRect TileMap::initRect_tile_back(char tile)
	{
		auto it = initRectBackMap.find(tile);
		if (it != initRectBackMap.end())
		{
			return it->second;
		}
		return sf::IntRect(0, 0, 0, 0);
	}

	void TileMap::init_texture() 
	{
	
		if (!block_T[0].loadFromFile("Textures/Textures_map/map.png")) 
		{
			std::cout << "Error -> TileMap -> couldn't load texture";
		}
		block_S[0].setTexture(block_T[0]);
	}
	
	void TileMap::add_tile(char letter, short int interaction, int i, int j)
	{
		tilemap[i][j].set_cord(initRect_tile_front(letter));
		tilemap[i][j].set_interaction(interaction);
	}

	void TileMap::delete_tile(char letter, short int interaction, int i, int j)
	{
		tilemap[i][j].set_cord(initRect_tile_back(letter));
		tilemap[i][j].set_interaction(interaction);
	}

	void TileMap::render(sf::RenderTarget& target)
	{
		for (int i = 0; i < mapW; i++)
		{
			for (int j = 0; j < mapH; j++)
			{
				block_S[0].setTextureRect(*tilemap[i][j].give_cord());
				block_S[0].setPosition(j * 64, i * 64);
				tilemap[i][j].tile_animation();
				target.draw(block_S[0]);
			}
		}
	}

	void TileMap::second_render(sf::RenderTarget& target)
	{
		for (int i = 0; i < mapW; i++)
		{
			for (int j = 0; j < mapH; j++)
			{
				block_S[0].setTextureRect(initRect_tile_back(tilemap[i][j].give_front_tile()));
				block_S[0].setPosition(j * sizeTexture, i * sizeTexture);
				//tilemap[i][j].tile_animation();
				target.draw(block_S[0]);
			}
		}
	}

	float TileMap::getMapWidth()
	{
		return mapH * sizeTexture;
	}

	float TileMap::getMapHeight()
	{
		return mapW * sizeTexture;
	}

	float TileMap::getSizeTexture()
	{
		return sizeTexture;
	}

	bool TileMap::isBlock(int i, int j)
	{
		if (tilemap[i][j].give_front_tile() != ' ')
			return true;
		return false;
	}

