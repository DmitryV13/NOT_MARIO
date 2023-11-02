#pragma once
#include "Player.h"
#include "TileMap.h"
#include "MyView.h"
#include "EvilBall.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event event;
	Player* player;
	EvilBall* evilBall;
	vector<EvilBall> evilball;
	TileMap sandbox;
	MyView myView;

	int numOfEnemy{60};
	double screenWidth;
	double screenHeight;

	void initWindow();
	void initPlayer();
	void initEvilBall();
public:
	Game(double screenWidth_, double screenHeight_);
	~Game();

	const sf::RenderWindow& getWindow() const;
	void updatePlayer();
	void updateEvilBall();
	void update();
	void updateView();
	void updateCollision();
	void renderEvilBall();
	void renderPLayer();
	void renderMap();
	void render();
};

