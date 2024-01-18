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
	//pause_menu->addGroup(50, 100, 0);

	CRect<float>* tmp = pause_menu->calculatePFNG(50, 100, 0);
	Group* t0 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
	t0->addGroupName("pause1", 30, font);
	delete tmp;

	t0->createElementLine();
	t0->addButton(45, font, "PAUSE1", Color::Red, 0);

	t0->createElementLine();
	t0->addButton(45, font, "PAUSE2", Color::Red, 1);

	t0->createElementLine();
	t0->addButton(45, font, "PAUSE3", Color::Red, 2);
	//
	//tmp = t0->calculatePFNII(50, 50, 0);
	//Group* t1 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
	//t1->addGroupName("0", 30, font);
	//t0->addIElement((InterfaceItem*)t1, 0);
	//delete tmp;
	//
	////t0->createGroupLine();
	//
	//tmp = t0->calculatePFNII(50, 50, 0);
	//Group* t2 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
	//t2->addGroupName("1", 30, font);
	//t0->addIElement((InterfaceItem*)t2, 0);
	//delete tmp;
	//
	//t0->createElementLine();
	//
	//tmp = t0->calculatePFNII(100, 50, 1);
	//Group* t3 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
	//t3->addGroupName("3", 40, font);
	//t0->addIElement((InterfaceItem*)t3, 1);
	//delete tmp;

	pause_menu->addGroup(t0, 0);
	//pause_menu->addGroupName(0, 0, "pause1", 30, font);
	//pause_menu->addGroupName(0, 0, "pause1", 30, font);
	pause_menu->addGroup(50, 100, 0);
	pause_menu->addGroupName(0, 1, "pause2", 30, font);
	//pause_menu->addGroupName(0, 1, "pause2", 30, font);

	game_menu = new GameMenu(window, sandbox.getMapWidth(), sandbox.getMapHeight(), screenWidth, screenHeight, &game_state, menuColor);
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
		delete game_menu;
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

	void Level::initEvilBall()
	{
		evil_ball_vector = new vector< EyeEvil*>();
		for (int i = 0; i < num_of_enemy_; i++)
		{
			EyeEvil* enemy = new EyeEvil(sandbox, player->getGeneralInfo());
			evil_ball_vector->push_back(enemy);
		}
		evil_Ball = new EyeEvil(sandbox, player->getGeneralInfo());
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
	evil_ball_vector = new vector<EyeEvil*>();
	chubacabras_vector_ = new vector<RedMutant*>();
	boss_vector = new vector<WolfBoss*>();
	evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo()));
	evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo()));
	evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo()));
	evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo()));
	Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	
	chubacabras_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));
	//chubacabras_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));
	//Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	////Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	//Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	//Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	boss_vector->push_back(new WolfBoss(sandbox, player->getGeneralInfo()));
	//chubacabras_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));
	Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo()));
	evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo()));
	//Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	//chubacabras_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));
	//chubacabras_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));
	//chubacabras_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));




}

void Level::updateEvilBall()
	{
	auto it = evil_ball_vector->begin();
	while (it != evil_ball_vector->end())
	{
		(*it)->update();

		if ((*it)->eye_state == EYE_EVIL_STATE::DEATH && (*it)->DEATH_timer.getElapsedTime().asSeconds() >= 5.1f)
		{
			
			it = evil_ball_vector->erase(it);
		}
		else
		{
			++it;
		}
	}
	}

	void Level::update_Kusaka()
	{


		auto it = Kusaka_vector->begin();
		while (it != Kusaka_vector->end())
		{
			(*it)->update();

			if ((*it)->kusaka_state == KUSAKA_STATE::KUSAKA_DEATH && (*it)->DEATH_timer.getElapsedTime().asSeconds() >= 5.1f)
			{

				it = Kusaka_vector->erase(it);
			}
			else
			{
				++it;
			}
		}
		//for (auto& enemy : *Kusaka_vector)
		//{
		//	enemy->update();
		//	//(*Kusaka_vector)[i]->update();
 	//	}
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
		game_menu->update(myView.getCurrentViewCords());
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

		//*player_gl_b = player->getGlobalBounds();
		//*player_pos = player->getPosition();
		//*player_vel = player->getVelocity();

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
				if (event.mouseWheelScroll.delta > 0) {
					player->change_weapon(1);
					//player->changeHP(-1);
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
		//game_menu->render();
		pause_menu->render();
		//window->display();
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

	void Level::initWeapons(){
		player->initWeapon({ reinterpret_cast<vector<Enemy*>*>(Kusaka_vector)
			, reinterpret_cast<vector<Enemy*>*>(evil_ball_vector)
			, reinterpret_cast<vector<Enemy*>*>(chubacabras_vector_)
			, reinterpret_cast<vector<Enemy*>*>(boss_vector) });
	}
