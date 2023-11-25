#pragma once
#include "Player.h"
#include "TileMap.h"
#include "MyView.h"
#include "Eye_evil.h"
#include "kusaka.h"
#include "chubacabra.h"

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
	vector<chubacabra*> chubacabras_vector_;
	int num_of_enemy_{ 10 };


	double screenWidth;
	double screenHeight;

	void initWindow();
	void initPlayer();
	void initView();
	void initEvilBall();
	void init_Kusaka();
	void init_chubacabra();
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
	void renderPLayer();
	void renderMap();
	void render();
	void renderEvilBall();
	void render_Kusaka();
	void render_chubacabra();
	void render_shot();
};

