#include "stdafx.h"
#include "TileMap.h"




	TileMap::TileMap() : sizeTexture(64), mapW(35), mapH(100), tilemap(36, std::vector<Tile*>(100))
	{
		init_tile_list();
		init_tile_list_back();
		
		TileFactory factory(mapW, mapH);
		
		for (int i = 0; i < mapW; i++)
			for (int j = 0; j < mapH; j++)
				tilemap[i][j] = give_tile(factory.give_letter(i, j));

		//delete_tile(27, 10, 'L');
		//delete_tile(30, 10, 'B');
		//delete_tile(29, 10, 'B');
		//delete_tile(28, 10, 'l');
		//delete_tile(30, 9, 'B');
		//delete_tile(29, 9, 'B');
		//delete_tile(28, 9, 'L');
		//delete_tile(30, 8, 'B');
		//delete_tile(29, 8, 'A');
	}

	void TileMap::init_tile_list()
	{
		tile_list['A'] = new Tile("grass_tile", 1, sizeTexture, sizeTexture, 'A');
		tile_list['C'] = new Tile("gass_tile_on_the_left", 1, sizeTexture, sizeTexture, 'C');
		tile_list['D'] = new Tile("gass_tile_on_the_right", 1, sizeTexture, sizeTexture, 'D');
		tile_list['L'] = new Tile("grass_tile_in_corner_left", 1, sizeTexture, sizeTexture, 'L');
		tile_list['P'] = new Tile("grass_tile_in_corner_right", 1, sizeTexture, sizeTexture, 'P');
		tile_list['B'] = new Tile("earth", 1, sizeTexture, sizeTexture, 'B');
		tile_list['S'] = new Tile("sand", 1, sizeTexture, sizeTexture, 'S');
		tile_list['G'] = new Tile("gravel", 1, sizeTexture, sizeTexture, 'G');
		tile_list['.'] = new Tile("ladder1", 0, sizeTexture, sizeTexture, '.');
		tile_list['_'] = new Tile("ladder2", 0, sizeTexture, sizeTexture, '_');
		tile_list['-'] = new Tile("ladder3", 0, sizeTexture, sizeTexture, '-');
		tile_list['='] = new Tile("ladder4", 0, sizeTexture, sizeTexture, '=');
		tile_list['+'] = new Tile("ladder5", 0, sizeTexture, sizeTexture, '+');
		tile_list['l'] = new Tile("ground8", 1, sizeTexture, sizeTexture, 'l');
		tile_list['r'] = new Tile("ground7", 1, sizeTexture, sizeTexture, 'r');
		tile_list['o'] = new Tile("bush", 0, sizeTexture, sizeTexture, 'o');
		tile_list['>'] = new Tile("directionSign1", 0, sizeTexture, sizeTexture, '>');
		tile_list['<'] = new Tile("directionSign2", 0, sizeTexture, sizeTexture, '<');
		tile_list['b'] = new Tile("box", 1, sizeTexture, sizeTexture, 'b');
		tile_list['1'] = new Tile("tree1", 0, 192, 256, '1');
		tile_list['2'] = new Tile("tree2", 0, 128, 256, '2');
		tile_list['3'] = new Tile("tree3", 0, 128, 256, '3');
		tile_list['4'] = new Tile("tree4", 0, 128, 192, '4');
		tile_list[' '] = new Tile();

		tile_list['W'] = new TileAnim("water_top_layer", 2, sizeTexture, sizeTexture,'W', 64, 4, 0.5);
		tile_list['w'] = new TileAnim("water_down_layer", 2, sizeTexture, sizeTexture, 'w', 64, 4, 0.5);
		tile_list['*'] = new TileAnim("water_down_layer_back", 2, sizeTexture, sizeTexture, '*', 64, 4, 0.5);
		tile_list['^'] = new TileAnim("water_top_layer_back", 2, sizeTexture, sizeTexture, '^', 64, 4, 0.5);
		tile_list['s'] = new TileAnim("spikes", 1, sizeTexture, sizeTexture, 's', 64, 3, 0.1);
		tile_list['m'] = new TileAnim("magma", 1, sizeTexture, sizeTexture, 'm', 64, 2, 0.5);
		tile_list['@'] = new TileAnim("health_potion", 0, 19, 39, '@', 19, 5, 0.3);
		
		tile_list['['] = new TileBox("chest1", 0, sizeTexture, sizeTexture, '[', 64, 4, 0.3);
		tile_list[']'] = new TileBox("chest2", 0, sizeTexture, sizeTexture, ']', 64, 4, 0.3);
		
	}

	void TileMap::init_tile_list_back()
	{
		tile_list_back['A'] = new Tile("grass_tile_back", 0, sizeTexture, sizeTexture, 'A');
		tile_list_back['C'] = new Tile("gass_tile_on_the_left_back", 0, sizeTexture, sizeTexture, 'C');
		tile_list_back['D'] = new Tile("gass_tile_on_the_right_back", 0, sizeTexture, sizeTexture, 'D');
		tile_list_back['L'] = new Tile("grass_tile_in_corner_left_back", 0, sizeTexture, sizeTexture, 'L');
		tile_list_back['P'] = new Tile("grass_tile_in_corner_right_back", 0, sizeTexture, sizeTexture, 'P');
		tile_list_back['B'] = new Tile("earth_back", 0, sizeTexture, sizeTexture, 'B');
		tile_list_back['S'] = new Tile("sand_back", 0, sizeTexture, sizeTexture, 'S');
		tile_list_back['G'] = new Tile("gravel_back", 0, sizeTexture, sizeTexture, 'G');
		tile_list_back['l'] = new Tile("ground8_back", 0, sizeTexture, sizeTexture, 'l');
		tile_list_back['r'] = new Tile("ground7_back", 0, sizeTexture, sizeTexture, 'r');
	}

	Tile* TileMap::give_tile(char letter)
	{
		auto it = tile_list.find(letter);
		if (it != tile_list.end()) {
			return it->second;
		}
		return tile_list[' '];
	}

	void TileMap::first_render(sf::RenderTarget& target, sf::FloatRect view_cords)
	{
		int start_i, start_j, finish_i, finish_j;

		start_i = (view_cords.top - ( view_cords.height/2)) / sizeTexture;
		start_j = (view_cords.left - (view_cords.width/2)) / sizeTexture;
		finish_i = (view_cords.top + (view_cords.height/2)) / sizeTexture;
		finish_j = (view_cords.left + (view_cords.width/2)) / sizeTexture;

		if(start_i > 1) start_i = start_i - 2;
		if(start_j > 1) start_j = start_j - 2;
		if(finish_i < mapW - 1) finish_i = finish_i + 2;
		if(finish_j < mapH - 1) finish_j = finish_j + 2;

		
		for (int i = start_i; i < finish_i; i++)
			for (int j = start_j; j < finish_j; j++) {
				if (tilemap[i][j] == tile_list['^']) {
					tilemap[i][j] = tile_list['W'];
					
				}
				if (tilemap[i][j] == tile_list['*']) {
					tilemap[i][j] = tile_list['w'];

				}
				if (tilemap[i][j] == tile_list['o']) {
					continue;
				}
				target.draw(tilemap[i][j]->render_tile(i, j));
			}
	}

	void TileMap::second_render(sf::RenderTarget& target, sf::FloatRect view_cords)
	{
		int start_i, start_j, finish_i, finish_j;
	
		start_i = (view_cords.top - (view_cords.height / 2)) / sizeTexture;
		start_j = (view_cords.left - (view_cords.width / 2)) / sizeTexture;
		finish_i = (view_cords.top + (view_cords.height / 2)) / sizeTexture;
		finish_j = (view_cords.left + (view_cords.width / 2)) / sizeTexture;
	
		if (start_i > 1) start_i = start_i - 2;
		if (start_j > 1) start_j = start_j - 2;
		if (finish_i < mapW - 1) finish_i = finish_i + 2;
		if (finish_j < mapH - 1) finish_j = finish_j + 2;
	
		for (int i = start_i; i < finish_i; i++)
		{
			for (int j = start_j; j < finish_j; j++)
			{
				if (tilemap[i][j] == tile_list['W']) {
					tilemap[i][j] = tile_list['^'];
					target.draw(tilemap[i][j]->render_tile(i, j));
				}
				if (tilemap[i][j] == tile_list['w']) {
					tilemap[i][j] = tile_list['*'];
					target.draw(tilemap[i][j]->render_tile(i, j));
				}
				if (tilemap[i][j] == tile_list['o']) {
					target.draw(tilemap[i][j]->render_tile(i, j));
				}
			}
		}
	}

	void TileMap::update(sf::RenderTarget& target, sf::FloatRect view_cords)
	{
		for (auto &it : tile_list) it.second->tile_animation();
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

	bool TileMap::isBlock(int i, int j){
		if (tilemap[i][j]->get_interaction() == 1)
			return true;
		return false;
	}

	void TileMap::add_tile(int i, int j, char association)
	{
		tilemap[i][j] = tile_list[association];
	}

	void TileMap::delete_tile(int i, int j, char association)
	{
		tilemap[i][j] = tile_list_back[association];
	}

