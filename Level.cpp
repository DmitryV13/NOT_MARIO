#include "stdafx.h"
#include "Level.h"

	Level::Level(double screen_w, double screen_h): screen_height(screen_h), screen_width(screen_w){
	}

	void Level::enter(sf::RenderWindow& window){
		Game* game = new Game(screen_width, screen_height);
		// level selection

		game->start(window);
	}