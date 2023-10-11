#include "stdafx.h"
#include "Game.h"

	Game::Game(double screenWidth_, double screenHeight_)
		:screenWidth(screenWidth_)
		,screenHeight(screenHeight_), myView(1500, 600, 1500, 600){
		initWindow();
		initPlayer();
	}
	
	Game::~Game(){
		delete player;
	}
	
	void Game::initWindow(){
		window.create(sf::VideoMode(screenWidth, screenHeight), "NOT_MARIO", sf::Style::Close | sf::Style::Titlebar);
		window.setFramerateLimit(144);
	}
	
	void Game::initPlayer(){
		player = new Player();
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
				}
				if (event.key.code == sf::Keyboard::S) {
					player->resetAnimationTimer();
				}
				if (event.key.code == sf::Keyboard::Space) {
					player->resetAnimationTimer();
				}
			}
		}
		updatePlayer();
		myView.updateView(player->getGlobalBounds());
		std::cout << "y - " << player->getPosition().y << ", x - " << player->getPosition().x<<std::endl;
		window.setView(myView.view);
		updateCollision();
	}

	void Game::updateCollision(){
		if ((player->getPosition().y + player->getGlobalBounds().height) > 73*600) {
			player->resetVelocityY();
			player->setPosition(
				player->getPosition().x,
				73*600 - player->getGlobalBounds().height);
		}
		if (player->getPosition().y < 0.f) {
			player->setPosition(
				player->getPosition().x,
				0);
		}
		if ((player->getPosition().x + player->getGlobalBounds().width) > 73*1500) {
			player->setPosition(
				73*1500 - player->getGlobalBounds().width,
				player->getPosition().y);
		}
		if (player->getPosition().x < 0) {
			player->setPosition(
				0,
				player->getPosition().y);
		}
	}
	void Game::renderMap() {
		map.render(window);
	}
	
	void Game::renderPLayer(){
		player->render(window);
	}
	
	void Game::updatePlayer(){
		player->update();
	}
	
	void Game::render(){
		window.clear(sf::Color::White);
		renderMap();
		renderPLayer();
		window.display();
	}
