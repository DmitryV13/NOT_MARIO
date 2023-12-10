#pragma once
#include "Player.h"
#include "TileMap.h"
#include "MyView.h"
#include "Eye_evil.h"
#include "kusaka.h"
#include "RedMutant.h"
#include "WolfBoss.h"
#include "GameMenu.h"
#include "ScaleParametrBar.h"
#include "GAME_STATE.h"

using namespace::sf;

class Level{
private:
	RenderWindow* window;
	GameMenu* game_menu;
	ScaleParametrBar* life_bar;
	Clock menu_timer;

	Event event;
	Player* player;
	TileMap sandbox;
	MyView myView;
	//Cursor* cursor;

	Eye_evil* evil_Ball;
	vector<Eye_evil*> evil_ball_vector;
	vector<kusaka*> Kusaka_vector;
	vector<RedMutant*> chubacabras_vector_;
	vector<WolfBoss*> boss_vector;
	int num_of_enemy_{ 1 };

	int numOfEnemy{ 60 };

	double screenWidth;
	double screenHeight;

	short game_state;

	//void initWindow();
	void initPlayer();
	void initView();
	void initEvilBall();
	void init_Kusaka();
	void init_chubacabra();
	void init_Wolf_boss();
public:
	Level(RenderWindow* window_, double screenWidth_, double screenHeight_, short level, Color menuColor);
	~Level();


	//const sf::RenderWindow& getWindow() const;
	void update();
	void updateEvents();
	void updatePlayer();
	void updateView();
	void updateCursor();
	void updateEvilBall();
	void update_Kusaka();
	void update_chubacabra();
	void update_Wolf_boss();
	void updateGameMenu();
	void updateGameState();
	void updateMap();
	void updateLifeBar();

	void renderGameMenu();
	void renderPLayer();
	void renderMap();
	void renderCursor();
	void render();
	void renderEvilBall();
	void render_Kusaka();
	void render_chubacabra();
	void render_Wolf_boss();
	void render_shot();
	void renderLifeBar();

	void start();
};
