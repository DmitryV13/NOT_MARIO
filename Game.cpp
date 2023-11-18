#include "stdafx.h"
#include "Game.h"

Game::Game(double screenWidth_, double screenHeight_)
	:screenWidth(screenWidth_)
	, screenHeight(screenHeight_)
	, myView(sandbox, screenWidth_, screenHeight_)
	, sandbox()
	, game_state(GAME_STATE::FINISHED) {
		//initWindow();
		std::cout << screenWidth << " " << screenHeight<<std::endl;
		initPlayer();
		//initEvilBall();
	}
	
	Game::~Game(){
		delete player;
		delete evilBall;
		evilball.clear();
	}
	
	//void Game::initWindow(){
	//	window.create(sf::VideoMode(screenWidth, screenHeight), "NOT_MARIO", sf::Style::Close | sf::Style::Titlebar);
	//	window.setFramerateLimit(144);
	//	window.setMouseCursorVisible(false);
	//	cursor = new Cursor();
	//}

	void Game::initEvilBall()
	{
		for (int i = 0; i < numOfEnemy; i++) {
			EvilBall enemy(sandbox);
			evilball.push_back(enemy);
		}
		evilBall = new EvilBall(sandbox);
	}

	void Game::updateEvilBall()
	{
		for (int i = 0; i < numOfEnemy; i++) {
			evilball[i].update();
		}
		evilBall->update();
	}

	void Game::updatePauseState(sf::RenderWindow& window){
		if (window.pollEvent(event) && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) {
			game_state = GAME_STATE::CONTINUES;
			player->resetIsFlying();
		}
	}

	void Game::updateGameState(sf::RenderWindow& window){
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				game_state = GAME_STATE::FINISHED;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) {
				if (game_state == GAME_STATE::PAUSED) {
					game_state = GAME_STATE::CONTINUES;
					
				}
				else {
					game_state = GAME_STATE::PAUSED;
					player->resetIsFlying();
				}
			}
		}
	}
	
	void Game::initPlayer(){
		player = new Player(sandbox);
	}

	void Game::initView(){

	}
	
	//const sf::RenderWindow& Game::getWindow() const{
	//	return window;
	//}
	
	void Game::update(sf::RenderWindow& window){
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				game_state = GAME_STATE::FINISHED;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) {
				
					game_state = GAME_STATE::PAUSED;
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
		//updateEvilBall();
		updateView();
		updateCollision();
		updateCursor();
	}

	void Game::updateView(){
		myView.updateView(player->getGlobalBounds());
	}

	void Game::updateCursor() {
		//sf::Vector2f p(sf::Mouse::getPosition(window));
		//cursor->update(sf::Vector2f(sf::Mouse::getPosition(window)));
		//std::cout << p.x << "  " << p.y<< std::endl;
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
	
	void Game::renderPLayer(sf::RenderWindow& window){
		player->render(window);
	}

	void Game::renderMap(sf::RenderWindow& window){
		sandbox.render(window);
	}

	void Game::renderCursor(sf::RenderWindow& window){
		//cursor->render(window);
	}
	
	void Game::updatePlayer(){
		player->update();
	}
	
	void Game::render(sf::RenderWindow& window){
		window.clear(sf::Color::White);
	
		renderMap(window);
		renderPLayer(window);
		//renderEvilBall(window);
		renderCursor(window);
		window.setView(myView.view);
		window.display();
	}

	void Game::renderEvilBall(sf::RenderWindow& window)
	{
		for (int i = 0; i < numOfEnemy; i++) {
			evilball[i].render(window);
		}

		

		evilBall->render(window);
	}

	void Game::start(sf::RenderWindow& window){
		game_state = GAME_STATE::CONTINUES;
		while (game_state != GAME_STATE::FINISHED) {
			//updateGameState(window);
			//if (game_state != GAME_STATE::PAUSED) {
			//	update(window);
			//	render(window);
			//}
			if (game_state == GAME_STATE::PAUSED) {
				updatePauseState(window);
			}else {
				update(window);
				render(window);
			}
		}
	}
