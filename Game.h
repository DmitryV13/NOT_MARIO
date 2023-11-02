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
	TileMap sandbox;
	MyView myView;

	EvilBall* evilBall;
	vector<EvilBall> evilball;

	int numOfEnemy{ 60 };

	double screenWidth;
	double screenHeight;

	void initWindow();
	void initPlayer();
	void initView();
	void initEvilBall();
public:
	Game(double screenWidth_, double screenHeight_);
	~Game();


	const sf::RenderWindow& getWindow() const;
	void updatePlayer();
	void update();
	void updateView();
	void updateCollision();
	void updateEvilBall();
	void renderPLayer();
	void renderMap();
	void render();
	void renderEvilBall();
};

