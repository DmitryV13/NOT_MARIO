#pragma once

using sf::Clock;

class Tile
{
protected:
	
	std::string tileName;
	sf::Texture tile_T;
	sf::Sprite	tile_S;
	short int texture_size_W;
	short int texture_size_H;
	short int interaction;
	bool player;
	char association;

	void init_texture(std::string Name);

public:

	Tile();
	Tile(std::string Name, short int inter, short int texture_size_w, short int texture_size_h, char ass);
	sf::Sprite render_tile(int i, int j);	
	bool give_player_info();
	short int get_interaction();
	virtual void tile_animation();
	
};
