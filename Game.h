#pragma once
#include "Player.h"
#include "TileMap.h"
#include "MyView.h"
#include "Eye_evil.h"
#include "kusaka.h"
#include "RedMutant.h"
#include "WolfBoss.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event event;
	Player* player;
	TileMap sandbox;
	MyView myView;


	Eye_evil* evil_Ball;
	vector<Eye_evil*> evil_ball_vector;
	vector<kusaka*> Kusaka_vector;
	vector<RedMutant*> chubacabras_vector_;
	vector<WolfBoss*> boss_vector;
	int num_of_enemy_{ 1 };


	double screenWidth;
	double screenHeight;

	void initWindow();
	void initPlayer();
	void initView();
	void initEvilBall();
	void init_Kusaka();
	void init_chubacabra();
	void init_Wolf_boss();
public:
	Game(double screenWidth_, double screenHeight_);
	~Game();


	const sf::RenderWindow& getWindow() const;
	void updatePlayer();
	void update();
	void updateView();
	void updateCollision();
	void updateEvilBall();
	void update_Kusaka();
	void update_chubacabra();
	void update_Wolf_boss();
	void renderPLayer();
	void renderMap();
	void render();
	void renderEvilBall();
	void render_Kusaka();
	void render_chubacabra();
	void render_Wolf_boss();
	void render_shot();
};

