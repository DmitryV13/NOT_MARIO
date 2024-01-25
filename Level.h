#pragma once
#include "BushKiller.h"
#include "GAME_STATE.h"
#include "BUTTON_STATE.h"
#include "POP_UP_WINDOW_STATE.h"
#include "Player.h"
#include "TileMap.h"
#include "MyView.h"
#include "EyeEvil.h"
#include "kusaka.h"
#include "RedMutant.h"
#include "WolfBoss.h"
#include "ScaleParametrBar.h"
#include "Enemy.h"
#include "PopUpWindow.h"
#include "hornet.h"
#include "HornetHive.h"
#include "TextureManager.h"
#include "Warehouse.h"

using namespace::sf;

class Level{
private:
	RenderWindow* window;

	PopUpWindow* pause_menu;
	ScaleParametrBar* life_bar;
	Clock menu_timer;

	TextureManager* t_manager;
	Warehouse* warehouse;

	Event event;
	Player* player;
	TileMap sandbox;
	MyView myView;
	//Cursor* cursor;

	vector<BushKiller*>* bush_killers_vector;
	vector<EyeEvil*>* evil_ball_vector;
	vector<kusaka*>* Kusaka_vector;
	vector<RedMutant*>* Red_Mutant_vector_;
	vector<WolfBoss*>* boss_vector;
	vector<hornet*>* hornet_vector;
	vector<HornetHive*>* hornet_hives_vector;

	int num_of_enemy_{ 5 };
	short regime;
	double screenWidth;
	double screenHeight;

	short game_state;


	//FloatRect* player_gl_b;
	//Vector2f* player_pos;
	//Vector2f* player_vel;
	//short* hp;

	//void initWindow();
	void initPlayer(short level);
	void initView();
	void init_enemy();
	void random_init_enemy();
public:
	Level(RenderWindow* window_, double screenWidth_, double screenHeight_, short level, Color menuColor, TextureManager* t_manager_, Warehouse* warehouse_, short regime_);
	~Level();

	void finishGame(float q);
	void continueGame(float q);

	//const sf::RenderWindow& getWindow() const;
	void update();
	void updateEvents();
	void updatePlayer();
	void updateView();
	void updateCursor();

	void update_Enemy();
	void updateGameMenu();
	void updateGameState();
	void updateMap();
	void updateLifeBar();

	void renderGameMenu();
	void renderPLayer();
	void renderMap();
	void renderCursor();
	void render();

	void renderEnemy();
	void renderLifeBar();

	void start();
	void initWeapons();
};

