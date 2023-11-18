#pragma once
#include "Player.h"
#include "TileMap.h"
#include "MyView.h"
#include "EvilBall.h"
#include "Cursor.h"

enum GAME_STATE{CONTINUES=0, PAUSED, FINISHED};

class Game{
private:
	//sf::RenderWindow window;
	sf::Event event;
	Player* player;
	TileMap sandbox;
	MyView myView;
	//Cursor* cursor;
	EvilBall* evilBall;
	vector<EvilBall> evilball;

	int numOfEnemy{ 60 };

	double screenWidth;
	double screenHeight;

	short game_state;

	//void initWindow();
	void initPlayer();
	void initView();
	void initEvilBall();
public:
	Game(double screenWidth_, double screenHeight_);
	~Game();


	//const sf::RenderWindow& getWindow() const;
	void update(sf::RenderWindow& window);
	void updatePlayer();
	void updateView();
	void updateCursor();
	void updateCollision();
	void updateEvilBall();
	void updatePauseState(sf::RenderWindow& window);
	void updateGameState(sf::RenderWindow& window);

	void renderPLayer(sf::RenderWindow& window);
	void renderMap(sf::RenderWindow& window);
	void renderCursor(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void renderEvilBall(sf::RenderWindow& window);

	void start(sf::RenderWindow& window);
};

