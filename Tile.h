#pragma once

using sf::Clock;

class Tile
{
private:

	bool player;
	char back_tile;
	char front_tile;
	short int interaction;
	short int animation_factor;
	short int animation_quantity;
	sf::IntRect *cord;
	Clock animationTimer;
	

public:
	Tile();
	Tile(sf::IntRect cord_, char f_b, char b_b, short int inter, short int anim_factor, short int anim_quantity);
	void tile_animation();
	char give_front_tile();
	char give_back_tile();
	bool give_player_info();
	sf::IntRect* give_cord();
	void set_cord(sf::IntRect cord_);
	void set_interaction(short int curr);
};
