#include "stdafx.h"
#include "TileMap.h"




	TileMap::TileMap() : sizeTexture(64), mapW(35), mapH(100)
	{
		init_background();
		init_tile_list();
		init_tile_list_back();
		init_tile_list_front();
		//имеем како нибудь параметр отвечающий за то какую карту будем делать, если генераци€, то 0. ≈сли один из уровней то 1.
		//принимаю параметр уровн€, дл€ генерации есть 3 уровн€. 1 мой, 2 ƒимы и 3 дл€ —ереженого. ƒл€ статик карт уровни так же даем от 1 и выше.
		int a = 1;
		int b = 1;
		
		if (a) {
			init_tilemap(mapW, mapH);

			//передаем параметры возращаем что нужно.
			TileFactory factory(mapW, mapH);

			char tmp_letter;

			for (int i = 0; i < mapW; i++)
			{
				for (int j = 0; j < mapH; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						tmp_letter = factory.give_letter(i, j, k);

						if (tmp_letter == '[' || tmp_letter == ']') {
							tilemap[i][j][1] = init_tile_box(tmp_letter);
							std::cout << i << ' ' << j << std::endl;
							continue;
						}
						if (k == 0) {
							tilemap[i][j][k] = give_tile_back(tmp_letter);
							continue;
						}
						if (k == 1) {
							tilemap[i][j][k] = give_tile(tmp_letter);
							continue;
						}
						if (k == 2) {
							tilemap[i][j][k] = give_tile_front(tmp_letter);
							continue;
						}
						if (tmp_letter == '[' || tmp_letter == ']') {
							tilemap[i][j][1] = init_tile_box(tmp_letter);
							std::cout << i << ' ' << j << std::endl;
							continue;
						}
					}
				}
			}
		}
		else 
		{
			init_generation_tilemap(mapW, mapH);

			//передаем параметрый возвращаем что нужно.
			TileFactory factory(mapW, mapH);

			for (int i = 0; i < mapW; i++) 
			{
				for (int j = 0; j < mapH; j++) 
				{
					generation_tilemap[i][j] = give_tile(factory.give_generation_letter(i, j));
				}
			}

		}
	}

	void TileMap::init_background()
	{
		if (!background_T.loadFromFile("Textures/Textures_map/background_test.png"))
		{
			std::cout << "Error -> background -> couldn't load texture";
		}
		backround_S.setTexture(background_T);
	}

	void TileMap::init_generation_tilemap(float mapW, float mapH)
	{
		generation_tilemap.resize(mapW);
		for (auto& innerVector : generation_tilemap)
			innerVector.resize(mapH);
	}

	void TileMap::init_tilemap(float mapW, float mapH)
	{
		tilemap.resize(mapW);
		for (auto& innerVector_1 : tilemap) {
			innerVector_1.resize(mapH);
			for (auto& innerVector_2 : innerVector_1) {
				innerVector_2.resize(3);
			}
		}
	}

	void TileMap::init_tile_list()
	{
		//ќсновные блоки
		tile_list['A'] = new Tile("grass_tile", 1, sizeTexture, sizeTexture, 'A');
		tile_list['C'] = new Tile("gass_tile_on_the_left", 1, sizeTexture, sizeTexture, 'C');
		tile_list['D'] = new Tile("gass_tile_on_the_right", 1, sizeTexture, sizeTexture, 'D');
		tile_list['L'] = new Tile("grass_tile_in_corner_left", 1, sizeTexture, sizeTexture, 'L');
		tile_list['P'] = new Tile("grass_tile_in_corner_right", 1, sizeTexture, sizeTexture, 'P');
		tile_list['B'] = new Tile("earth", 1, sizeTexture, sizeTexture, 'B');
		tile_list['S'] = new Tile("sand", 1, sizeTexture, sizeTexture, 'S');
		tile_list['G'] = new Tile("gravel", 1, sizeTexture, sizeTexture, 'G');
		tile_list['l'] = new Tile("ground8", 1, sizeTexture, sizeTexture, 'l');
		tile_list['r'] = new Tile("ground7", 1, sizeTexture, sizeTexture, 'r');
		tile_list['W'] = new TileAnim("water_top_layer", 2, sizeTexture, sizeTexture, 'W', 64, 4, 0.5);
		tile_list['w'] = new TileAnim("water_down_layer", 2, sizeTexture, sizeTexture, 'w', 64, 4, 0.5);
		tile_list[' '] = new Tile();

		//‘ункциональные и декоративыне блоки.
		tile_list['.'] = new Tile("ladder1", 0, sizeTexture, sizeTexture, '.');
		tile_list['_'] = new Tile("ladder2", 0, sizeTexture, sizeTexture, '_');
		tile_list['-'] = new Tile("ladder3", 0, sizeTexture, sizeTexture, '-');
		tile_list['='] = new Tile("ladder4", 0, sizeTexture, sizeTexture, '=');
		tile_list['+'] = new Tile("ladder5", 0, sizeTexture, sizeTexture, '+');
		tile_list['>'] = new Tile("directionSign1", 0, sizeTexture, sizeTexture, '>');
		tile_list['<'] = new Tile("directionSign2", 0, sizeTexture, sizeTexture, '<');
		tile_list['b'] = new Tile("box", 1, sizeTexture, sizeTexture, 'b');
		tile_list['1'] = new Tile("tree1", 0, 192, 256, '1');
		tile_list['2'] = new Tile("tree2", 0, 128, 256, '2');
		tile_list['3'] = new Tile("tree3", 0, 128, 256, '3');
		tile_list['4'] = new Tile("tree4", 0, 128, 192, '4');
		tile_list['^'] = new TileAnim("water_top_layer_back", 2, sizeTexture, sizeTexture, '^', 64, 4, 0.5);
		tile_list['*'] = new TileAnim("water_down_layer_back", 2, sizeTexture, sizeTexture, '*', 64, 4, 0.5);
		
		
		//јнимированные блоки
		tile_list['s'] = new TileAnim("spikes", 1, sizeTexture, sizeTexture, 's', 64, 3, 0.1);
		tile_list['m'] = new TileAnim("magma", 1, sizeTexture, sizeTexture, 'm', 64, 2, 0.5);
		tile_list['@'] = new TileAnim("health_potion", 0, 19, 39, '@', 19, 5, 0.3);
		
	}

	void TileMap::init_tile_list_back()
	{
		//Ѕлоки заднего фона, отображаемые при разрушение блока, либо расположенные разработчиком в местах где они необходимы(пещеры, €мы и другое)
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
		tile_list_back['W'] = new TileAnim("water_top_layer", 2, sizeTexture, sizeTexture, 'W', 64, 4, 0.5);
		tile_list_back['w'] = new TileAnim("water_down_layer", 2, sizeTexture, sizeTexture, 'w', 64, 4, 0.5);

	}

	void TileMap::init_tile_list_front()
	{
		//Ѕлоки переднего плана, служащие фильтром дл€ погружени€ игрока в различные структуры на карте(вода, лава и другое)
		tile_list_front['w'] = new TileAnim("water_down_layer_back", 2, sizeTexture, sizeTexture, 'w', 64, 4, 0.5);
		tile_list_front['W'] = new TileAnim("water_top_layer_back", 2, sizeTexture, sizeTexture, 'W', 64, 4, 0.5);
		tile_list_front['o'] = new Tile("bush", 0, sizeTexture, sizeTexture, 'o');
	}


	Tile* TileMap::init_tile_box(char letter)
	{
		std::string name = "chest";
		name += letter;
		return new TileBox(name, 0, sizeTexture, sizeTexture, letter, 64, 4, 0.3);
	}

	Tile* TileMap::give_tile(char letter)
	{
		auto it = tile_list.find(letter);
		if (it != tile_list.end()) {
			return it->second;
		}
		return tile_list[' '];
	}

	Tile* TileMap::give_tile_back(char letter)
	{
		auto it = tile_list_back.find(letter);
		if (it != tile_list_back.end()) {
			return it->second;
		}
		return tile_list[' '];
	}

	Tile* TileMap::give_tile_front(char letter)
	{
		auto it = tile_list_front.find(letter);
		if (it != tile_list_front.end()) {
			return it->second;
		}
		return tile_list[' '];
	}


	void TileMap::background_render(sf::RenderTarget& target, sf::FloatRect view_cords)
	{
		int x, y;
		y = (view_cords.top - (view_cords.height / 2));
		x = (view_cords.left - (view_cords.width / 2));


		backround_S.setPosition(x * coefficient_X, y * coefficient_Y);
		target.draw(backround_S);

	}

	void TileMap::first_render(sf::RenderTarget& target, sf::FloatRect view_cords)
	{
		int start_i, start_j, finish_i, finish_j;

		//start_i = (view_cords.top - ( view_cords.height/2)) / sizeTexture;
		start_j = (view_cords.left - (view_cords.width/2)) / sizeTexture;
		finish_i = (view_cords.top + (view_cords.height/2)) / sizeTexture;
		finish_j = (view_cords.left + (view_cords.width/2)) / sizeTexture;

		//if(start_i > 1) start_i = start_i - 2;
		if(start_j > 1) start_j = start_j - 2;
		if(finish_i < mapW - 1) finish_i = finish_i + 2;
		if(finish_j < mapH - 1) finish_j = finish_j + 2;

		
		for (int i = 0; i < mapW; i++) {
			for (int j = start_j; j < finish_j; j++) {
				for (int k = 0; k < 2; k++) {
					target.draw(tilemap[i][j][k]->render_tile(i, j));
				}
			}
		}
	}

	void TileMap::second_render(sf::RenderTarget& target, sf::FloatRect view_cords)
	{
		int start_i, start_j, finish_i, finish_j;
	
		//start_i = (view_cords.top - (view_cords.height / 2)) / sizeTexture;
		start_j = (view_cords.left - (view_cords.width / 2)) / sizeTexture;
		finish_i = (view_cords.top + (view_cords.height / 2)) / sizeTexture;
		finish_j = (view_cords.left + (view_cords.width / 2)) / sizeTexture;
	
		//if (start_i > 1) start_i = start_i - 2;
		if (start_j > 1) start_j = start_j - 2;
		if (finish_i < mapW - 1) finish_i = finish_i + 2;
		if (finish_j < mapH - 1) finish_j = finish_j + 2;
	
		for (int i = 0; i < mapW; i++)
		{
			for (int j = start_j; j < finish_j; j++)
			{			
				target.draw(tilemap[i][j][2]->render_tile(i, j));	
			}
		}
	}

	void TileMap::update(sf::RenderTarget& target, sf::FloatRect view_cords)
	{
		for (auto& it : tile_list_back) {
			it.second->tile_animation();
		}
		for (auto& it : tile_list) {
			it.second->tile_animation();
		}
		for (auto& it : tile_list_front) {
			it.second->tile_animation();
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

	bool TileMap::isBlock(int i, int j){
		if (tilemap[i][j][1]->get_interaction() == 1)
			return true;
		return false;
	}


	void TileMap::add_tile(int i, int j, char association)
	{
		if (tilemap[i][j][1] == tile_list[' ']) {
			tilemap[i][j][1] = tile_list[association];
		}
	}

	void TileMap::delete_tile(int i, int j, char association)
	{
		if (tilemap[i][j][0] != tile_list[' ']) {
			tilemap[i][j][1] = tile_list[' '];
			return;
		}
		tilemap[i][j][1] = tile_list[' '];
		tilemap[i][j][0] = give_tile_back(association);
	}

