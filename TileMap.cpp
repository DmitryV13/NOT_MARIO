#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
	:sizeTexture(60)
	, mapW(40)
	, mapH(200) {

	init_texture();
	TileFactory factory(40,200);
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
#include "stdafx.h"
#include "TileMap.h"




	TileMap::TileMap() : sizeTexture(64), mapH(100), mapW(1000)
	{
		init_background();
		init_tile_list();
		init_tile_list_back();
		init_tile_list_front();
		init_tilemap(mapH, mapW);

		int a = 0;
		int b = 3;

		if (a) {
			TileFactory factory(mapH, mapW, a, b);

			char tmp_letter;
			for (int i = 0; i < mapH; i++)
			{
				for (int j = 0; j < mapW; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						tmp_letter = factory.give_letter(i, j, k);
						if (tmp_letter == '[' || tmp_letter == ']') {
							tilemap[i][j][1] = init_tile_box(tmp_letter);
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
					}
				}
			}
		}
		else
		{
			TileFactory factory(mapH, mapW, a, b);

			char tmp_letter;
			for (int i = 0; i < mapH; i++)
			{
				for (int j = 0; j < mapW; j++)
				{
					tmp_letter = factory.give_generation_letter(i, j);
					if (tmp_letter != 'W' && tmp_letter != 'w') {
						tilemap[i][j][0] = give_tile_back(' ');
						tilemap[i][j][1] = give_tile(tmp_letter);
						tilemap[i][j][2] = give_tile_front(' ');
						continue;
					}
					if (tmp_letter == 'W') {
						tilemap[i][j][0] = give_tile_back(tmp_letter);
						tilemap[i][j][1] = give_tile(' ');
						tilemap[i][j][2] = give_tile_front(tmp_letter);
						continue;
					}
					if (tmp_letter == 'w') {
						tilemap[i][j][0] = give_tile_back(tmp_letter);
						tilemap[i][j][1] = give_tile(' ');
						tilemap[i][j][2] = give_tile_front(tmp_letter);
						continue;
					}
				}
			}

		}
	}

	void TileMap::init_background()
	{
		if (!background_T.loadFromFile("Textures/Textures_map/background_1.png"))
		{
			std::cout << "Error -> background -> couldn't load texture";
		}
		backround_S.setTexture(background_T);
		init_coeff(backround_S.getTextureRect());
	}

	void TileMap::init_coeff(sf::IntRect pos)
	{
		coefficient_X = static_cast <float> (sizeTexture * mapW) / (static_cast<float> (pos.width) - 1600);
		coefficient_Y = static_cast <float> (sizeTexture * mapH) / (static_cast<float> (pos.height) - 900);
	}

	void TileMap::init_tilemap(float mapH, float mapW)
	{
		tilemap.resize(mapH);
		for (auto& innerVector_1 : tilemap) {
			innerVector_1.resize(mapW);
			for (auto& innerVector_2 : innerVector_1) {
				innerVector_2.resize(3);
			}
		}
	}

	void TileMap::init_tile_list()
	{
		//Основные блоки
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

		//Функциональные и декоративыне блоки.
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


		//Анимированные блоки
		tile_list['s'] = new TileAnim("spikes", 1, sizeTexture, sizeTexture, 's', 64, 3, 0.1);
		tile_list['m'] = new TileAnim("magma", 1, sizeTexture, sizeTexture, 'm', 64, 2, 0.5);
		tile_list['@'] = new TileAnim("health_potion", 0, 19, 39, '@', 19, 5, 0.3);

	}

	void TileMap::init_tile_list_back()
	{
		//Блоки заднего фона, отображаемые при разрушение блока, либо расположенные разработчиком в местах где они необходимы(пещеры, ямы и другое)
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
		//Блоки переднего плана, служащие фильтром для погружения игрока в различные структуры на карте(вода, лава и другое)
		tile_list_front['w'] = new TileAnim("water_down_layer_back", 2, sizeTexture, sizeTexture, 'w', 64, 4, 0.5);
		tile_list_front['W'] = new TileAnim("water_top_layer_back", 2, sizeTexture, sizeTexture, 'W', 64, 4, 0.5);
		tile_list_front['o'] = new Tile("bush", 0, sizeTexture, sizeTexture, 'o');
	}

	Tile* TileMap::init_tile_box(char letter)
	{
		std::string name = "chest";
		name += letter;
		tilebox.push_back(new TileBox(name, 0, sizeTexture, sizeTexture, letter, 64, 4, 0.3));
		return *tilebox.cbegin();
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
		float x, y, l, k;
		l = (view_cords.left - (view_cords.width / 2));
		k = (view_cords.top - (view_cords.height / 2));
		x = l / coefficient_X;
		y = k / coefficient_Y;
		l = l - x;
		k = k - y;
		backround_S.setPosition(l, k);
		target.draw(backround_S);

	}

	void TileMap::first_render(sf::RenderTarget& target, sf::FloatRect view_cords)
	{
		int start_i, start_j, finish_i, finish_j;

		start_i = (view_cords.top - (view_cords.height / 2)) / sizeTexture;
		start_j = (view_cords.left - (view_cords.width / 2)) / sizeTexture;
		finish_i = (view_cords.top + (view_cords.height / 2)) / sizeTexture;
		finish_j = (view_cords.left + (view_cords.width / 2)) / sizeTexture;

		if (start_i > 0) start_i = start_i - 1;
		if (start_j > 0) start_j = start_j - 1;
		if (finish_i < mapH) finish_i = finish_i + 1;
		if (finish_j < mapW) finish_j = finish_j + 1;

		if (start_i > 1) start_i = start_i - 2;
		if (start_j > 1) start_j = start_j - 2;
		if (finish_i < mapH - 1) finish_i = finish_i + 2;
		if (finish_j < mapW - 1) finish_j = finish_j + 2;


		for (int i = start_i; i < finish_i; i++) {
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

		start_i = (view_cords.top - (view_cords.height / 2)) / sizeTexture;
		start_j = (view_cords.left - (view_cords.width / 2)) / sizeTexture;
		finish_i = (view_cords.top + (view_cords.height / 2)) / sizeTexture;
		finish_j = (view_cords.left + (view_cords.width / 2)) / sizeTexture;

		if (start_i > 0) start_i = start_i - 1;
		if (start_j > 0) start_j = start_j - 1;
		if (finish_i < mapH) finish_i = finish_i + 1;
		if (finish_j < mapW) finish_j = finish_j + 1;

		if (start_i > 1) start_i = start_i - 2;
		if (start_j > 1) start_j = start_j - 2;
		if (finish_i < mapH - 1) finish_i = finish_i + 2;
		if (finish_j < mapW - 1) finish_j = finish_j + 2;

		for (int i = start_i; i < finish_i; i++)
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
		for (auto& it : tilebox) {
			it->box_animation();
		}
	}


	float TileMap::getMapWidth()
	{
		return mapW * sizeTexture;
	}

	float TileMap::getMapHeight()
	{
		return mapH * sizeTexture;
	}

	float TileMap::getSizeTexture()
	{
		return sizeTexture;
	}

	bool TileMap::isBlock(int i, int j) {
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

