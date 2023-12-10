#include "stdafx.h"
#include "Level.h"

Level::Level(RenderWindow* window_, double screenWidth_, double screenHeight_, short level)
	:window(window_)
	,screenWidth(screenWidth_)
	,screenHeight(screenHeight_)
	,myView(sandbox, screenWidth_, screenHeight_)
	,sandbox(level)
	,game_state(GAME_STATE::FINISHED) {
	game_menu = new GameMenu(window, sandbox.getMapWidth(), sandbox.getMapHeight(), &game_state);
		initPlayer();
		menu_timer.restart();
		initEvilBall();
		init_Kusaka();
		init_chubacabra();
		//init_Wolf_boss();
	}
	
	Level::~Level(){
		delete player;
		delete evil_Ball;
		for (auto& enemy : evil_ball_vector) {
			delete enemy;
		}
		evil_ball_vector.clear();
		for (auto& enemy : Kusaka_vector) {
			delete enemy;
		}
		Kusaka_vector.clear();
		for (auto& enemy : chubacabras_vector_) {
			delete enemy;
		}
		chubacabras_vector_.clear();
		for (auto& enemy : boss_vector) {
			delete enemy;
		}
		boss_vector.clear();
	}

	void Level::initEvilBall()
	{
		for (int i = 0; i < num_of_enemy_; i++)
		{
			Eye_evil* enemy = new Eye_evil(sandbox, *player);
			evil_ball_vector.push_back(enemy);
		}
		evil_Ball = new Eye_evil(sandbox, *player);
	}

	void Level::init_Kusaka()
	{
		for (int i = 0; i < num_of_enemy_; i++)
		{
			kusaka* enemy = new kusaka(sandbox, *player);
			Kusaka_vector.push_back(enemy);
		}
	}

	void Level::init_chubacabra()
	{
		for (int i = 0; i < num_of_enemy_; i++)
		{
			RedMutant* enemy = new RedMutant(sandbox, *player);
			chubacabras_vector_.push_back(enemy);
		}
	}

	void Level::init_Wolf_boss()
	{
		for (int i = 0; i < num_of_enemy_; i++)
		{
			WolfBoss* enemy = new WolfBoss(sandbox, *player);
			boss_vector.push_back(enemy);
		}
	}

	void Level::updateEvilBall()
	{
		for (int i = 0; i < num_of_enemy_; i++)
		{
			evil_ball_vector[i]->update();
		}
		evil_Ball->update();
	}

	void Level::update_Kusaka()
	{
		for (int i = 0; i < num_of_enemy_; i++)
		{
			Kusaka_vector[i]->update();
 		}
	}

	void Level::update_chubacabra()
	{
		for (int i = 0; i < num_of_enemy_; i++)
		{
			chubacabras_vector_[i]->update();
		}
	}

	void Level::update_Wolf_boss()
	{
		for (int i = 0; i < num_of_enemy_; i++)
		{
			boss_vector[i]->update();
		}
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

	void Level::updateMap(){
		sandbox.update(*window, myView.getCurrentViewCords());
	}
	
	void Level::initPlayer(){
		player = new Player(sandbox);
	}

	void Level::initView(){

	}
	
	void Level::update(){
		updatePlayer();
		
		updateEvilBall();
		update_Kusaka();
		update_chubacabra();
		//update_Wolf_boss();

		updateView();
		updateCursor();
		updateMap();
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
	
	void Level::renderGameMenu(){
		game_menu->render();
	}

	void Level::renderPLayer(){
		player->render(*window);
	}

	void Level::renderMap(){
		sandbox.background_render(*window, myView.getCurrentViewCords());
		sandbox.first_render(*window, myView.getCurrentViewCords());
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

		renderEvilBall();
		render_Kusaka();
		render_chubacabra();
		render_shot();
		//render_Wolf_boss();

		sandbox.second_render(*window, myView.getCurrentViewCords());
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
		for (int i = 0; i < num_of_enemy_; i++)
		{
			evil_ball_vector[i]->render(*window);
		}

		evil_Ball->render(*window);
	}

	void Level::render_Kusaka()
	{
		for (int i = 0; i < num_of_enemy_; i++)
		{
			Kusaka_vector[i]->render(*window);
		}
	}

	void Level::render_chubacabra()
	{
		for (int i = 0; i < num_of_enemy_; i++)
		{
			chubacabras_vector_[i]->render(*window);
		}
	}

	void Level::render_Wolf_boss()
	{
		for (int i = 0; i < num_of_enemy_; i++)
		{
			boss_vector[i]->render(*window);
		}
	}

	void Level::render_shot()
	{
		if (evil_Ball->laser_existence())
		{
			if (evil_Ball->laser_existence())
				evil_Ball->draw_laser(0, *window);

		}
		for (int i = 0; i < num_of_enemy_; i++)
		{
			if (evil_ball_vector[i]->laser_existence())
			{

				evil_ball_vector[i]->draw_laser(1, *window);

			}
		}
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
