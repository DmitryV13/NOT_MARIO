#pragma once
class Tile
{
private:

	char front_tile;
	char back_tile = ' ';
	bool player = false;
	sf::IntRect cord;

public:
	Tile();
	Tile( sf::IntRect cord_, char f_b );
	char give_front_tile();
	char give_back_tile();
	bool give_player_info();
	sf::IntRect give_cord();
};
