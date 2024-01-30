#pragma once

using sf::Clock;

class Tile
{
protected:

	std::string tileName;
	sf::Texture tile_T;
	sf::Sprite	tile_S;
	float texture_size_W;
	float texture_size_H;
	short int interaction;
	char association;
	bool player;

	void init_texture(std::string Name);

public:

	Tile();
	Tile(std::string Name, short int inter, float texture_size_w, float texture_size_h, char ass);
	virtual ~Tile();
	sf::Sprite render_tile(int i, int j);
	bool give_player_info();
	short int get_interaction();
	char give_tile_association();
	virtual void tile_animation();
	virtual void box_animation();
	void setTilePresence(bool presence);
};
