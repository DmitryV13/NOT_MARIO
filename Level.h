#pragma once
#include "Player.h"
#include "TileMap.h"
#include "MyView.h"
#include "EvilBall.h"
#include "GameMenu.h"
#include "GAME_STATE.h"

using namespace::sf;

class Level{
private:
	RenderWindow* window;
	GameMenu* game_menu;
	Clock menu_timer;

	Event event;
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
	Level(RenderWindow* window_, double screenWidth_, double screenHeight_, short level);
	~Level();


	//const sf::RenderWindow& getWindow() const;
	void update();
	void updateEvents();
	void updatePlayer();
	void updateView();
	void updateCursor();
	void updateEvilBall();
	void updateGameMenu();
	void updateGameState();
	void updateMap();

	void renderGameMenu();
	void renderPLayer();
	void renderMap();
	void renderCursor();
	void render();
	void renderEvilBall();

	void start();
};

