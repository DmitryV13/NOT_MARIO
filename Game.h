#pragma once
#include "Player.h"
#include "TileMap.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event event;
	Player* player;
	//TileMap sandbox;

	double screenWidth;
	double screenHeight;

	void initWindow();
	void initPlayer();
public:
	Game(double screenWidth_, double screenHeight_);
	~Game();

	const sf::RenderWindow& getWindow() const;
	void updatePlayer();
	void update();
	void updateCollision();
	void renderPLayer();
	void renderMap();
	void render();
};

