#pragma once
#include "units/enemies/BushKiller.h"
#include "game/enums/GAME_STATE.h"
#include "ui/enums/BUTTON_STATE.h"
#include "ui/enums/POP_UP_WINDOW_STATE.h"
#include "units/player/Player.h"
#include "map/TileMap.h"
#include "screens/MyView.h"
#include "units/enemies/EyeEvil.h"
#include "units/enemies/kusaka.h"
#include "units/enemies/RedMutant.h"
#include "units/enemies/WolfBoss.h"
#include "ui/ScaleParametrBar.h"
#include "units/enemies/Enemy.h"
#include "ui/PopUpWindow.h"
#include "units/enemies/hornet.h"
#include "units/enemies/HornetHive.h"
#include "common/TextureManager.h"
#include "game/Warehouse.h"
#include "ui/Form.h"
#include "ui/CheckboxItem.h"
#include "map/enums/OBJECT_TYPE.h"

using namespace::sf;

class Level{
private:
	RenderWindow* window;

	ScaleParameterBar* life_bar;
	Clock menu_timer;

	Group* all_static_items;
	PopUpWindow* pause_menu;
	PopUpWindow* level_inventory;
	PopUpWindow* chest_items;
	Form* form;
	Object* available_object;

	TextureManager* t_manager;
	Warehouse* warehouse;

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

	short object_available;

	int num_of_enemy_{ 1 };
	short regime;
	double screenWidth;
	double screenHeight;

	short game_state;


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
	//void updateLifeBar();
	void updateObjectsCollision();

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

