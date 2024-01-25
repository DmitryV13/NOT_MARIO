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

	EyeEvil* evil_Ball;
	vector<BushKiller*>* bush_killers_vector;
	vector<EyeEvil*>* evil_ball_vector;
	vector<kusaka*>* Kusaka_vector;
	vector<RedMutant*>* Red_Mutant_vector_;
	vector<WolfBoss*>* boss_vector;
	vector<hornet*>* hornet_vector;
	vector<HornetHive*>* hornet_hives_vector;


	int num_of_enemy_{ 12 };
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
	void initEvilBall();
	void init_Kusaka();
	void init_chubacabra();
	void init_Wolf_boss();
	void init_BushKiller();
	void init_enemy();
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
	void updateEvilBall();
	void update_Kusaka();
	void update_BushKiller();
	void update_Red_Mutant();
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

	void renderEnemy();
	void renderEvilBall();
	void render_Kusaka();
	void render_chubacabra();
	void render_BushKiller();
	void render_Wolf_boss();
	void render_shot();
	void renderLifeBar();

	void start();
	void initWeapons();
};

