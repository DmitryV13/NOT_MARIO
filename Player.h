#pragma once
#include "Map.h"
#include <SFML/Graphics.hpp>
using sf::Sprite;
using sf::RenderWindow;

class Player
{
	Map map;
	Sprite player;
	float playerSpeed;

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
};