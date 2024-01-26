#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(short level) : sizeTexture(64), mapH(50), mapW(100)
{
	init_background();
	init_tile_list();
	init_tile_list_back();
	init_tile_list_front();
	init_tilemap(mapH, mapW);
	init_level(level);
	init_objects(level);
	init_animObjects(level);
	init_movingObjects(level);
	init_movingAnimObjects(level);
	init_switch(level);
	init_chest(level);
	init_pos_enemy();
}

TileMap::~TileMap()
{
	free_memory();
}

void TileMap::free_memory()
{
	for (auto& it : object) delete it;
	for (auto& it : tile_list) delete it.second;
	for (auto& it : tile_list_back) delete it.second;
	for (auto& it : tile_list_front) delete it.second;
}

void TileMap::init_pos_enemy()
{

	enemy_position.push({ 989.f,2800.f });
	enemy_position.push({ 920.f,2890.f });
	enemy_position.push({ 1020.f,2890.f });

	enemy_position.push({ 1079.f,1270.f });
	enemy_position.push({ 6105.f,2740.f });
	enemy_position.push({ 5525.f,2100.f });
	enemy_position.push({ 6091.f,2230.f });
	enemy_position.push({ 4613.f,2740.f });
	enemy_position.push({ 1993.f,2920.f });

	enemy_position.push({ 2020.f,2920.f });

	enemy_position.push({ 989.f,2890.f });
	enemy_position.push({ 5622.f,400.f });
	enemy_position.push({ 1101.f,480.f });
	enemy_position.push({ 1100.f,1590.f });
	enemy_position.push({ 790.f,1590.f });
	enemy_position.push({ 380.f,1540.f });

}

void TileMap::writeFile()
{

}

sf::Vector2f TileMap::cord_enemy()
{
	sf::Vector2f tmp_pos(0,0);
	if (enemy_position.empty())return tmp_pos;
	pair<float, float> tmp = enemy_position.top();
	tmp_pos.x = tmp.first;
	tmp_pos.y = tmp.second;
	enemy_position.pop();
	return tmp_pos;
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
	coefficient_X = static_cast<float>(sizeTexture * mapW) / (static_cast<float>(pos.width) - 1920);
	coefficient_Y = static_cast<float>(sizeTexture * mapH) / (static_cast<float>(pos.height) - 1080);
}

void TileMap::init_tilemap(float mapH, float mapW)
{
	tilemap = new Tile ***[mapH];
	for (int i = 0; i < mapH; ++i) {
		tilemap[i] = new Tile **[mapW];
		for (int j = 0; j < mapW; ++j) {
			tilemap[i][j] = new Tile *[3];
		}
	}
}

void TileMap::init_level(short int level)
{
	if (level >= 4) {
		std::string level_ = std::to_string(level-bim);
		std::string path = "Maps/level"+level_+"/level.txt";
		std::ifstream fin;
		fin.open(path);
		if (!fin.is_open()) {
			std::cout << "Error: the file is not open or not found " << std::endl;
			return;
		}
		char tmp_letter;
		for (int i = 0; i < mapH; i++)
		{
			for (int j = 0; j < mapW; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					fin >> tmp_letter;
					if (k == 0)
					{
						tilemap[i][j][k] = give_tile_back(tmp_letter);
						continue;
					}
					if (k == 1)
					{
						;
						tilemap[i][j][k] = give_tile(tmp_letter);
						continue;
					}
					if (k == 2)
					{
						tilemap[i][j][k] = give_tile_front(tmp_letter);
						continue;
					}
				}
			}
		}
		fin.close();
		return;
	}
	TileFactory factory(mapH, mapW, level);
	char tmp_letter;
	for (int i = 0; i < mapH; i++)
	{
		for (int j = 0; j < mapW; j++)
		{
			tmp_letter = factory.give_generation_letter(i, j);
			if (tmp_letter != 'W' && tmp_letter != 'w')
			{
				tilemap[i][j][0] = give_tile_back('`');
				tilemap[i][j][1] = give_tile(tmp_letter);
				tilemap[i][j][2] = give_tile_front('`');
				continue;
			}
			if (tmp_letter == 'W')
			{
				tilemap[i][j][0] = give_tile_back(tmp_letter);
				tilemap[i][j][1] = give_tile('`');
				tilemap[i][j][2] = give_tile_front(tmp_letter);
				continue;
			}
			if (tmp_letter == 'w')
			{
				tilemap[i][j][0] = give_tile_back(tmp_letter);
				tilemap[i][j][1] = give_tile('`');
				tilemap[i][j][2] = give_tile_front(tmp_letter);
				continue;
			}
		}
	}
}

void TileMap::init_objects(short int level)
{
	std::string level_ = std::to_string(level-bim);
	std::string path = "Maps/level"+level_+"/Object.txt";
	std::ifstream fin;
	fin.open(path);
	if (!fin.is_open()) {
		std::cout << "Error: the file is not open or not found " << std::endl;
		return;
	}
	std::string objectName;
	float pos_x, pos_y;
	short size_w, size_h;

	while (fin >> objectName >> pos_x >> pos_y >> size_w >> size_h)
	{
		object.push_back(new MovingObject{ objectName, pos_x, pos_y, size_w, size_h});
	}

	fin.close();
}

void TileMap::init_animObjects(short int level)
{
	std::string level_ = std::to_string(level-bim);
	std::string path = "Maps/level"+level_+"/AnimObject.txt";
	std::ifstream fin;
	fin.open(path);
	if (!fin.is_open()) {
		std::cout << "Error: the file is not open or not found " << std::endl;
		return;
	}
	std::string objectName;
	float pos_x, pos_y, anim_t;
	short size_w, size_h, anim_f, anim_q;

	while (fin >> objectName >> pos_x >> pos_y >> size_w >> size_h >> anim_f >> anim_q >> anim_t)
	{
		object.push_back(new AnimObject{ objectName, pos_x, pos_y, size_w, size_h, anim_f, anim_q, anim_t});
	}
	fin.close();
}

void TileMap::init_movingObjects(short int level)
{
	std::string level_ = std::to_string(level-bim);
	std::string path = "Maps/level"+level_+"/MovingObject.txt";
	std::ifstream fin;
	fin.open(path);
	if (!fin.is_open()) {
		std::cout << "Error: the file is not open or not found " << std::endl;
		return;
	}
	std::string objectName;
	float pos_x, pos_y;
	short size_w, size_h;
	float move_l, move_r, move_u, move_d, speed;

	while (fin >> objectName >> pos_x >> pos_y >> size_w >> size_h >> move_l >> move_r >> move_u >> move_d >> speed)
	{
		object.push_back(new MovingObject{ objectName, pos_x, pos_y, size_w, size_h, move_l, move_r, move_u, move_d, speed });
	}
	
	fin.close();
}

void TileMap::init_movingAnimObjects(short int level)
{
	std::string level_ = std::to_string(level-bim);
	std::string path = "Maps/level"+level_+"/MovingAnimObject.txt";
	std::ifstream fin;
	fin.open(path);
	if (!fin.is_open()) {
		std::cout << "Error: the file is not open or not found " << std::endl;
		return;
	}
	std::string objectName;
	float pos_x, pos_y;
	short size_w, size_h, anim_f, anim_q;
	float anim_t, move_l, move_r, move_u, move_d, speed;

	while (fin >> objectName >> pos_x >> pos_y >> size_w >> size_h >> anim_f >> anim_q >> anim_t >> move_l >> move_r >> move_u >> move_d >> speed)
	{
		object.push_back(new MovingAnimObject{ objectName, pos_x, pos_y, size_w, size_h, anim_f, anim_q, anim_t, move_l, move_r, move_u, move_d, speed });
	}
	fin.close();
}

void TileMap::init_switch(short int level)
{
	std::string level_ = std::to_string(level-bim);
	std::vector<Object*> tmpObject;
	std::string path_ = "Maps/level"+level_+"/forSwitch.txt";
	std::ifstream fin_;
	fin_.open(path_);
	if (!fin_.is_open()) {
		std::cout << "Error: the file is not open or not found " << std::endl;
		return;
	}
	std::string objectName_;
	float pos_x_, pos_y_;
	short size_w_, size_h_;
	float move_l_, move_r_, move_u_, move_d_, speed_;

	while (fin_ >> objectName_ >> pos_x_ >> pos_y_ >> size_w_ >> size_h_ >> move_l_ >> move_r_ >> move_u_ >> move_d_ >> speed_)
	{
		tmpObject.push_back(new MovingObject{ objectName_, pos_x_, pos_y_, size_w_, size_h_, move_l_, move_r_, move_u_, move_d_, speed_});
	}

	fin_.close();

	std::string path = "Maps/level"+level_+"/Switch.txt";
	std::ifstream fin;
	fin.open(path);
	if (!fin.is_open()) {
		std::cout << "Error: the file is not open or not found " << std::endl;
		return;
	}
	std::string objectName;
	float pos_x, pos_y, anim_t;
	short size_w, size_h, anim_f, anim_q;
	auto it = tmpObject.begin();

	while (fin >> objectName >> pos_x >> pos_y >> size_w >> size_h >> anim_f >> anim_q >> anim_t)
	{
		if (it != tmpObject.end()) {
			object.push_back(new Switch{ objectName, pos_x, pos_y, size_w, size_h, anim_f, anim_q, anim_t, *it });
			++it;
		}
		object.push_back(new Switch{ objectName, pos_x, pos_y, size_w, size_h, anim_f, anim_q, anim_t});
	}
	fin.close();
	for (auto it : tmpObject) object.push_back(it);
	tmpObject.clear();
}

void TileMap::init_chest(short int level)
{
	std::string level_ = std::to_string(level-bim);
	std::string path = "Maps/level"+level_+"/Chest.txt";
	std::ifstream fin;
	fin.open(path);
	if (!fin.is_open()) {
		std::cout << "Error: the file is not open or not found " << std::endl;
		return;
	}
	std::string objectName;
	float pos_x, pos_y, anim_t;
	short size_w, size_h, anim_f, anim_q, filling;

	while (fin >> objectName >> pos_x >> pos_y >> size_w >> size_h >> anim_f >> anim_q >> anim_t >> filling)
	{
		object.push_back(new Chest{ objectName, pos_x, pos_y, size_w, size_h, anim_f, anim_q, anim_t, filling});
	}

	fin.close();
}

void TileMap::init_tile_list()
{
	//Основные блоки
	tile_list['A'] = new Tile("grass_tile", 1, sizeTexture, sizeTexture, 'A');
	tile_list['C'] = new Tile("grass_tile_on_the_left", 1, sizeTexture, sizeTexture, 'C');
	tile_list['D'] = new Tile("grass_tile_on_the_right", 1, sizeTexture, sizeTexture, 'D');
	tile_list['L'] = new Tile("grass_tile_in_corner_left", 1, sizeTexture, sizeTexture, 'L');
	tile_list['P'] = new Tile("grass_tile_in_corner_right", 1, sizeTexture, sizeTexture, 'P');
	tile_list['B'] = new Tile("earth", 1, sizeTexture, sizeTexture, 'B');
	tile_list['S'] = new Tile("sand", 1, sizeTexture, sizeTexture, 'S');
	tile_list['G'] = new Tile("gravel", 1, sizeTexture, sizeTexture, 'G');
	tile_list['l'] = new Tile("ground8", 1, sizeTexture, sizeTexture, 'l');
	tile_list['r'] = new Tile("ground7", 1, sizeTexture, sizeTexture, 'r');
	tile_list['W'] = new TileAnim("water_top_layer", 2, sizeTexture, sizeTexture, 'W', 64, 4, 0.5);
	tile_list['w'] = new TileAnim("water_down_layer", 2, sizeTexture, sizeTexture, 'w', 64, 4, 0.5);
	tile_list['`'] = new Tile();

	//Функциональные и декоративыне блоки.
	tile_list['^'] = new Tile("ladder1", 0, sizeTexture, sizeTexture, '.');
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
	tile_list['5'] = new Tile("cactus1", 0, sizeTexture, sizeTexture, '5');
	tile_list['6'] = new Tile("cactus2", 0, sizeTexture, sizeTexture, '6');


	//Анимированные блоки
	tile_list['s'] = new TileAnim("spikes", 1, sizeTexture, sizeTexture, 's', 64, 3, 0.1);
	tile_list['m'] = new TileAnim("magma", 1, sizeTexture, sizeTexture, 'm', 64, 2, 0.5);
	tile_list['@'] = new TileAnim("health_potion", 0, 19, 39, '@', 19, 5, 0.3);
}

void TileMap::init_tile_list_back()
{
	//Блоки заднего фона, отображаемые при разрушение блока, либо расположенные разработчиком в местах где они необходимы(пещеры, ямы и другое)
	tile_list_back['A'] = new Tile("grass_tile_back", 0, sizeTexture, sizeTexture, 'A');
	tile_list_back['C'] = new Tile("grass_tile_on_the_left_back", 0, sizeTexture, sizeTexture, 'C');
	tile_list_back['D'] = new Tile("grass_tile_on_the_right_back", 0, sizeTexture, sizeTexture, 'D');
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

Tile* TileMap::give_tile(char letter)
{
	auto it = tile_list.find(letter);
	if (it != tile_list.end())
	{
		return it->second;
	}
	return tile_list['`'];
}

Tile* TileMap::give_tile_back(char letter)
{
	auto it = tile_list_back.find(letter);
	if (it != tile_list_back.end())
	{
		return it->second;
	}
	return tile_list['`'];
}

Tile* TileMap::give_tile_front(char letter)
{
	auto it = tile_list_front.find(letter);
	if (it != tile_list_front.end())
	{
		return it->second;
	}
	return tile_list['`'];
}

void TileMap::first_renderObject(sf::RenderTarget& target)
{
	for (auto& it : object) {
		it->render_object(target);
		it->animation_object();
		it->moveHorizont();
		it->moveVertically();
	}
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


	for (int i = start_i; i < finish_i; i++)
	{
		for (int j = start_j; j < finish_j; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				target.draw(tilemap[i][j][k]->render_tile(i, j));
			}
		}
	}
	first_renderObject(target);
	
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
	for (auto& it : tile_list_back)
	{
		it.second->tile_animation();
	}
	for (auto& it : tile_list)
	{
		it.second->tile_animation();
	}
	for (auto& it : tile_list_front)
	{
		it.second->tile_animation();
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

bool TileMap::isBlock(int i, int j)
{
	if (tilemap[i][j][1]->get_interaction() == 1)
		return true;
	return false;
}

bool TileMap::outOfMap(int i, int j)
{
	if (i < 0 || i >= mapH || j < 0 || j >= mapW)
	{
		return false;
	}
	return true;
}

void TileMap::add_tile(int i, int j, char association)
{
	if (tilemap[i][j][1] == tile_list['`'])
	{
		tilemap[i][j][1] = tile_list[association];
	}
}

void TileMap::delete_tile(int i, int j, char association)
{
	if (tilemap[i][j][0] != tile_list['`'])
	{
		tilemap[i][j][1] = tile_list['`'];
		return;
	}
	tilemap[i][j][1] = tile_list['`'];
	tilemap[i][j][0] = give_tile_back(association);
}

bool TileMap::isOccupied(int i, int j)
{
	return tilemap[i][j][1]->give_player_info();
}

void TileMap::updatePlayerPresence(int indexI[], int indexJ[]){

}

short TileMap::getInteraction(int i, int j){
	return tilemap[i][j][1]->get_interaction();
}

vector<Object*>& TileMap::getObjects()
{
	return object;
}
