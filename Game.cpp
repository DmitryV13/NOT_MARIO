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
	}
	
	Game::~Game(){
		delete player;
		delete evilBall;
		evilball.clear();
		
	}
	
	void Game::initWindow(){
		window.create(sf::VideoMode(screenWidth, screenHeight), "NOT_MARIO", sf::Style::Close | sf::Style::Titlebar);
		window.setFramerateLimit(144);
	}
	
	void Game::initPlayer(){
		player = new Player(sandbox);
	}

	void Game::initEvilBall()
	{
		for (int i = 0; i < numOfEnemy; i++) {
			EvilBall enemy(sandbox);
			evilball.push_back(enemy);
		}
		evilBall = new EvilBall(sandbox);
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
		updateView();
		updateCollision();
		//updateCollisionMap();
	}

	void Game::updateView(){
		myView.updateView(player->getGlobalBounds());
		
	}

	void Game::updateCollision(){
		if ((player->getPosition().y + player->getGlobalBounds().height) > 1460.f) {
			player->resetVelocityY();
			player->setPosition(
				player->getPosition().x,
				1460.f - player->getGlobalBounds().height);
			player->resetJumpAccess();
		}
		if (player->getPosition().y < 0.f) {
			player->setPosition(
				player->getPosition().x,
				0);
		}
		if ((player->getPosition().x + player->getGlobalBounds().width) > 7300.f) {
			player->setPosition(
				7300.f - player->getGlobalBounds().width,
				player->getPosition().y);
		}
		if (player->getPosition().x < 0) {
			player->setPosition(
				0,
				player->getPosition().y);
		}



		
	}

void Game::renderEvilBall()
{
	for (int i = 0; i < numOfEnemy; i++) {
		evilball[i].render(window);
	}
	evilBall->render(window);
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

void Game::updateEvilBall()
{
	for (int i = 0; i < numOfEnemy; i++) {
		evilball[i].update();
	}
	evilBall->update();
}

void Game::render(){
		window.clear(sf::Color::White);
	
		renderMap();
		renderPLayer();
		renderEvilBall();
		window.setView(myView.view);
		window.display();
	}
