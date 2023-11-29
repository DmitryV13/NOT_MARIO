#include "stdafx.h"
#include "Level.h"

Level::Level(RenderWindow* window_, double screenWidth_, double screenHeight_)
	:window(window_)
	,screenWidth(screenWidth_)
	,screenHeight(screenHeight_)
	,myView(sandbox, screenWidth_, screenHeight_)
	,sandbox()
	,game_state(GAME_STATE::FINISHED) {
	game_menu = new GameMenu(window, sandbox.getMapWidth(), sandbox.getMapHeight(), &game_state);
		initPlayer();
		menu_timer.restart();
		//initEvilBall();
	}
	
	Level::~Level(){
		delete player;
		//delete evilBall;
		evilball.clear();
	}

	void Level::initEvilBall()
	{
		for (int i = 0; i <numOfEnemy; i++) {
			EvilBall enemy(sandbox);
			evilball.push_back(enemy);
		}
		//evilBall = new EvilBall(sandbox);
	}

	void Level::updateEvilBall()
	{
		for (int i = 0; i < numOfEnemy; i++) {
			evilball[i].update();
		}
		//evilBall->update();
	}

	void Level::updateGameMenu(){
		game_menu->update(myView.getCurrentViewCords());
	}

	void Level::updateGameState(){
		if (menu_timer.getElapsedTime().asSeconds() >= 0.2f) {
			if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
				if (game_state == GAME_STATE::PAUSED) {
					game_state = GAME_STATE::CONTINUES;
				}
				else {
					game_state = GAME_STATE::PAUSED;
				}
				menu_timer.restart();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				game_state = GAME_STATE::FINISHED;
			}
		}
	}
	
	void Level::initPlayer(){
		player = new Player(sandbox);
	}

	void Level::initView(){

	}
	
	void Level::update(){
		updatePlayer();
		//updateEvilBall();
		updateView();
		updateCollision();
		updateCursor();
	}

	void Level::updateEvents(){
		while (window->pollEvent(event)) {
			if (event.type == Event::KeyReleased) {

				if (event.key.code == Keyboard::D) {
					player->resetAnimationTimer();
				}
				if (event.key.code == Keyboard::A) {
					player->resetAnimationTimer();
				}
				if (event.key.code == Keyboard::W) {
					player->resetAnimationTimer();
					player->resetIsFlying();
				}
				if (event.key.code == Keyboard::S) {
					player->resetAnimationTimer();
				}
				if (event.key.code == Keyboard::Space) {
					player->resetAnimationTimer();
					player->resetNTHJump();
				}
			}
			if (event.type == sf::Event::MouseWheelScrolled) {
				if (event.mouseWheelScroll.delta > 0) {
					player->change_weapon(1);
				}
				else {
					player->change_weapon(-1);
				}
			}
		}
	}

	void Level::updateView(){
		myView.updateView(player->getGlobalBounds());
	}

	void Level::updateCursor() {
		//sf::Vector2f p(sf::Mouse::getPosition(window));
		//cursor->update(sf::Vector2f(sf::Mouse::getPosition(window)));
		//std::cout << p.x << "  " << p.y<< std::endl;
	}

	void Level::updateCollision(){
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
	
	void Level::renderGameMenu(){
		game_menu->render();
	}

	void Level::renderPLayer(){
		player->render(*window);
	}

	void Level::renderMap(){
		sandbox.render(*window);
	}

	void Level::renderCursor(){
		//cursor->render(window);
	}
	
	void Level::updatePlayer(){
		player->update(window, myView.getCurrentViewCords());
	}
	
	void Level::render(){
		window->clear(Color::White);
	
		renderMap();
		renderPLayer();
		//renderEvilBall();
		//renderCursor();
		window->setView(myView.view);

		if (game_state == GAME_STATE::PAUSED) {
			updateGameMenu();
			renderGameMenu();
		}

		window->display();
	}

	void Level::renderEvilBall()
	{
		for (int i = 0; i < numOfEnemy; i++) {
			evilball[i].render(window);
		}

		

		//evilBall->render(*window);
	}

	void Level::start(){
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		//	int y = 0;
		//}
		game_state = GAME_STATE::CONTINUES;
		while (game_state != GAME_STATE::FINISHED) {
			updateGameState();
			updateEvents();
			//this bug has a beneficial effect
			if (game_state != GAME_STATE::PAUSED) {
				update();
			}
			render();
		}
	}
