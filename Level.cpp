#include "stdafx.h"
#include "Level.h"

Level::Level(RenderWindow* window_, double screenWidth_, double screenHeight_, short level, Color menuColor)
	:window(window_)
	,screenWidth(screenWidth_)
	,screenHeight(screenHeight_)
	,myView(sandbox, screenWidth_, screenHeight_)
	,sandbox(level)
	,game_state(GAME_STATE::FINISHED)
	,regime(2) {//1-random generation, 2-set positions

	Font* font = new Font();
	if (!font->loadFromFile("Fonts/Pixel.ttf")) {
		std::cout << "Error -> RoadMap -> couldn't load text font" << std::endl;
	}


	pause_menu = new PopUpWindow(screenWidth, screenHeight, 800, 800, window);
	pause_menu->addLabel(screenWidth, screenHeight, "Menu", font, 60, 10);
	pause_menu->addBackground(sandbox.getMapWidth(), sandbox.getMapHeight(), Color(59, 66, 73, 87));
	pause_menu->createGroupLine();

	CRect<float>* tmp = pause_menu->calculatePFNG(100, 100, 0);
	Group* t0 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
	delete tmp;
	
	t0->createElementLine();
	t0->addButton(40, font, "CONTINUE", menuColor, 0, 0);
	
	t0->createElementLine();
	t0->addButton(40, font, "SETTINGS", menuColor, 1, 1);

	t0->createElementLine();
	t0->addButton(40, font, "BACK TO LOBBY", menuColor, 2, 2);
	
	//t0->createElementLine();
	//tmp = t0->calculatePFNII(40, 50, 1);
	//Group* t3 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
	//t3->addGroupName("3", 31, font);
	//t0->addIElement((InterfaceItem*)t3, 1);
	//delete tmp;

	
	//t3->createElementLine();
	//t3->addButton(20, font, "CLOSE", Color::Red, 2);
	//t3->setAlignment("k", "bottom 0");
	//	pause_menu->addCallback(t0->getButtonState("BACK TO LOBBY"), (short)BUTTON_STATE::BTN_ACTIVE, &PopUpWindow::setPUWStateC, pause_menu);
	t0->setAlignment("center auto", "center 50");
	pause_menu->addCallback(t0->getButtonState(0), (short)BUTTON_STATE::BTN_ACTIVE, 0, &Level::continueGame , this);
	
	pause_menu->addCallback(t0->getButtonState(2), (short)BUTTON_STATE::BTN_ACTIVE, 0, &Level::finishGame, this);
	pause_menu->addGroup(t0, 0);
	//pause_menu->addGroup(50, 50, 0);
	//pause_menu->addGroupName(0, 1, "pause2", 31, font);

	life_bar = new ScaleParametrBar();

	initPlayer();
		menu_timer.restart();
		if(regime == -1)
		{
			initEvilBall();
			init_Kusaka();
			init_chubacabra();
			init_Wolf_boss();
			initWeapons();
		}else if(level == 4)
		{
			init_enemy();
			initWeapons();
		}
		
	}
	
	Level::~Level(){
		delete player;
		delete life_bar;
		delete evil_Ball;
		for (auto& enemy : *evil_ball_vector) {
			delete enemy;
		}
		evil_ball_vector->clear();
		for (auto& enemy : *Kusaka_vector) {
			delete enemy;
		}
		Kusaka_vector->clear();
		for (auto& enemy : *chubacabras_vector_) {
			delete enemy;
		}
		chubacabras_vector_->clear();
		//for (auto& enemy : *boss_vector) {
		//	delete enemy;
		//}
		//boss_vector->clear();
	}

	void Level::finishGame(float q){
		game_state = GAME_STATE::FINISHED;
	}

	void Level::continueGame(float q){
		game_state = GAME_STATE::CONTINUES;
	}

	void Level::initEvilBall()
	{
		evil_ball_vector = new vector< Eye_evil*>();
		for (int i = 0; i < num_of_enemy_; i++)
		{
			Eye_evil* enemy = new Eye_evil(sandbox, player->getGeneralInfo());
			evil_ball_vector->push_back(enemy);
		}
		evil_Ball = new Eye_evil(sandbox, player->getGeneralInfo());
	}

	void Level::init_Kusaka()
	{
		Kusaka_vector = new vector<kusaka*>();
		for (int i = 0; i < num_of_enemy_; i++)
		{
			kusaka* enemy = new kusaka(sandbox, player->getGeneralInfo());
			Kusaka_vector->push_back(enemy);
		}
	}

	void Level::init_chubacabra()
	{
		chubacabras_vector_ = new vector<RedMutant*>();
		for (int i = 0; i < num_of_enemy_; i++)
		{
			RedMutant* enemy = new RedMutant(sandbox, player->getGeneralInfo());
			chubacabras_vector_->push_back(enemy);
		}
	}

	void Level::init_Wolf_boss()
	{
		boss_vector = new vector<WolfBoss*>();
		for (int i = 0; i < num_of_enemy_; i++)
		{
			WolfBoss* enemy = new WolfBoss(sandbox, player->getGeneralInfo());
			boss_vector->push_back(enemy);
		}
	}

	void Level::init_enemy()
{
	Kusaka_vector = new vector<kusaka*>();
	Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	evil_ball_vector = new vector<Eye_evil*>();
	evil_ball_vector->push_back(new Eye_evil(sandbox, player->getGeneralInfo()));
	evil_ball_vector->push_back(new Eye_evil(sandbox, player->getGeneralInfo()));
	chubacabras_vector_ = new vector<RedMutant*>();
	chubacabras_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));
	chubacabras_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));
	chubacabras_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));
	boss_vector = new vector<WolfBoss*>();
	boss_vector->push_back(new WolfBoss(sandbox, player->getGeneralInfo()));

}

	void Level::initWeapons() {
		player->initWeapon({ reinterpret_cast<vector<Enemy*>*>(Kusaka_vector)
			, reinterpret_cast<vector<Enemy*>*>(evil_ball_vector)
			, reinterpret_cast<vector<Enemy*>*>(chubacabras_vector_)
			, reinterpret_cast<vector<Enemy*>*>(boss_vector) });
	}
	
	void Level::updateEvilBall()
	{
	for (auto& enemy : *evil_ball_vector)
		{
			(enemy)->update();
			//(*evil_ball_vector)[i]->update();
		}
	}

	void Level::update_Kusaka()
	{
		for (auto& enemy : *Kusaka_vector)
		{
			enemy->update();
			//(*Kusaka_vector)[i]->update();
 		}
	}

	void Level::update_chubacabra()
	{
		for (auto& enemy : *chubacabras_vector_)
		{
			enemy->update();
			//(*chubacabras_vector_)[i]->update();
		}
	}

	void Level::update_Wolf_boss()
	{
		for (auto& enemy : *boss_vector)

		{
			enemy->update();
			//(*boss_vector)[i]->update();
		}
	}

	void Level::updateGameMenu(){
		pause_menu->update(myView.getCurrentViewCords());
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

	void Level::updateLifeBar(){
		life_bar->updateScaleWidth(player->getHP());
		life_bar->update(myView.getCurrentViewCords(), screenWidth, screenHeight);
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
		update_Wolf_boss();

		updateView();
		updateCursor();
		updateMap();
		updateLifeBar();
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
				if (game_state == GAME_STATE::CONTINUES) {
					if (event.mouseWheelScroll.delta > 0) {
						player->change_weapon(1);
					}
					else {
						player->change_weapon(-1);
					}
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
		pause_menu->render();
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
		render_Wolf_boss();

		sandbox.second_render(*window, myView.getCurrentViewCords());
		renderCursor();
		window->setView(myView.view);

		renderLifeBar();

		if (game_state == GAME_STATE::PAUSED) {
			updateGameMenu();
			renderGameMenu();
		}
		window->display();
	}

	void Level::renderEvilBall()
	{
		for (auto& enemy : *evil_ball_vector)

		{
			enemy->render(*window);
			//(*evil_ball_vector)[i]->render(*window);
		}

		
	}

	void Level::render_Kusaka()
	{
		for (auto& enemy : *Kusaka_vector)
		{
			enemy->render(*window);
			//(*Kusaka_vector)[i]->render(*window);
		}
	}

	void Level::render_chubacabra()
	{
		for (auto& enemy : *chubacabras_vector_)
		{
			//(*chubacabras_vector_)[i]->render(*window);
			enemy->render(*window);
		}
	}

	void Level::render_Wolf_boss()
	{
		for (auto& enemy : *boss_vector)
		{
			//(*boss_vector)[i]->render(*window);
			enemy->render(*window);
		}
	}

	void Level::render_shot()
	{
		
		for (auto& enemy : *evil_ball_vector)
		{
			//if ((*evil_ball_vector)[i]->laser_existence())
			if (enemy->laser_existence())
			{

				//(*evil_ball_vector)[i]->draw_laser(1, *window);
				enemy->draw_laser(1, *window);

			}
		}
	}

	void Level::renderLifeBar(){
		life_bar->render(window);
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
