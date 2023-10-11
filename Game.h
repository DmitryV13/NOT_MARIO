#pragma once
#include "Player.h"
#include "TileMap.h"
#include "MyView.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event event;
	Player* player;
	TileMap map;
	MyView myView;

	double screenWidth;
	double screenHeight;

	void initWindow();
	void initPlayer();
	void initView();
public:
	Game(double screenWidth_, double screenHeight_);
	~Game();

	const sf::RenderWindow& getWindow() const;
	void updatePlayer();
	void update();
	void updateCollision();
	void renderMap();
	void renderPLayer();
	void render();
};

