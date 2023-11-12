#include "stdafx.h"
#include "Game.h"

	Game::Game(double screenWidth_, double screenHeight_)
		:screenWidth(screenWidth_)
		,screenHeight(screenHeight_)
		,myView(sandbox, screenWidth_, screenHeight_)
		,sandbox(){
		initWindow();
		initPlayer();
		initEvilBall();
		init_Kusaka();
	}
	
	Game::~Game(){
		delete player;
		delete evil_Ball;
		evil_ball_vector.clear();
		Kusaka_vector.clear();
	}
	
	void Game::initWindow(){
		window.create(sf::VideoMode(screenWidth, screenHeight), "NOT_MARIO", sf::Style::Close | sf::Style::Titlebar);
		window.setFramerateLimit(144);
	}

	void Game::initEvilBall()
	{
		for (int i = 0; i < num_of_enemy_; i++) {
			Eye_evil *enemy = new Eye_evil(sandbox);
			evil_ball_vector.push_back(enemy);
		}
		evil_Ball = new Eye_evil(sandbox);
	}

void Game::init_Kusaka()
{
	for (int i = 0; i < num_of_enemy_; i++) {
		kusaka *enemy = new kusaka(sandbox);
		Kusaka_vector.push_back(enemy);
	}
}

void Game::updateEvilBall()
	{
		for (int i = 0; i < num_of_enemy_; i++) {
			evil_ball_vector[i]->update();
		}
		evil_Ball->update();
	}

void Game::update_Kusaka()
{
	for (int i = 0; i < num_of_enemy_; i++) {
		Kusaka_vector[i]->update();
	}
}

void Game::initPlayer(){
		player = new Player(sandbox);
	}

	void Game::initView(){

	}
	
	const sf::RenderWindow& Game::getWindow() const{
		return window;
	}
	
	void Game::update(){
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::D) {
					player->resetAnimationTimer();
				}
				if (event.key.code == sf::Keyboard::A) {
					player->resetAnimationTimer();
				}
				if (event.key.code == sf::Keyboard::W) {
					player->resetAnimationTimer();
					player->resetIsFlying();
				}
				if (event.key.code == sf::Keyboard::S) {
					player->resetAnimationTimer();
				}
				if (event.key.code == sf::Keyboard::Space) {
					player->resetAnimationTimer();
					player->resetNTHJump();
				}
			}
		}
		updatePlayer();
		updateEvilBall();
		update_Kusaka();
		updateView();
		updateCollision();
		
		//updateCollisionMap();
	}

	void Game::updateView(){
		myView.updateView(player->getGlobalBounds());
	}

	void Game::updateCollision(){
		if ((player->getPosition().y + player->getGlobalBounds().height) > 2400.f) {
			player->resetVelocityY();
			player->setPosition(
				player->getPosition().x,
				2400.f - player->getGlobalBounds().height);
			player->resetJumpAccess();
		}
		if (player->getPosition().y < 0.f) {
			player->setPosition(
				player->getPosition().x,
				0);
		}
		if ((player->getPosition().x + player->getGlobalBounds().width) > 12000.f) {
			player->setPosition(
				12000.f - player->getGlobalBounds().width,
				player->getPosition().y);
		}
		if (player->getPosition().x < 0) {
			player->setPosition(
				0,
				player->getPosition().y);
		}
	}
	
	void Game::renderPLayer(){
		player->render(window);
	}

	void Game::renderMap(){
		sandbox.render(window);
	}
	
	void Game::updatePlayer(){
		player->update();
	}
	
	void Game::render(){
		window.clear(sf::Color::White);
	
		renderMap();
		renderPLayer();
		renderEvilBall();
		render_Kusaka();
		render_shot();
		
		window.setView(myView.view);
		window.display();
	}

	void Game::renderEvilBall()
	{
		for (int i = 0; i < num_of_enemy_; i++) {
			evil_ball_vector[i]->render(window);
			
		}
		
		evil_Ball->render(window);
		
	}

void Game::render_Kusaka()
{
	for (int i = 0; i < num_of_enemy_; i++) {
		Kusaka_vector[i]->render(window);
	}
}

void Game::render_shot()
{
	if (evil_Ball->laser_existence())
	{
		for (int i = 0; i < evil_Ball->laser_length(); i++)
		{
			evil_Ball->draw_laser(i, window);
		}
	}
	for (int i = 0; i < num_of_enemy_; i++) {
		if (evil_ball_vector[i]->laser_existence())
		{
			for (int j = 0; j < evil_ball_vector[i]->laser_length(); j++)
			{
				evil_ball_vector[i]->draw_laser(j, window);
			}
		}
	}
}
