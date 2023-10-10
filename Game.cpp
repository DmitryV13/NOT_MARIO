#include "stdafx.h"
#include "Game.h"

	Game::Game(double screenWidth_, double screenHeight_)
		:screenWidth(screenWidth_)
		,screenHeight(screenHeight_){
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
					player->resetNTHJump();
				}
			}
		}
		updatePlayer();
		updateCollision();
	}

	void Game::updateCollision(){
		if ((player->getPosition().y + player->getGlobalBounds().height) > window.getSize().y) {
			player->resetVelocityY();
			player->setPosition(
				player->getPosition().x,
				window.getSize().y - player->getGlobalBounds().height);
			player->resetJumpAccess();
		}
		if (player->getPosition().y < 0.f) {
			player->setPosition(
				player->getPosition().x,
				0);
		}
		if ((player->getPosition().x + player->getGlobalBounds().width) > window.getSize().x) {
			player->setPosition(
				window.getSize().x - player->getGlobalBounds().width,
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

	//void Game::renderMap(){
	//	sandbox.render(window);
	//}
	
	void Game::updatePlayer(){
		player->update();
	}
	
	void Game::render(){
		window.clear(sf::Color::White);
	
		//renderMap();
		renderPLayer();
		window.display();
	}
