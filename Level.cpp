#include "stdafx.h"
#include "Level.h"

Level::Level(RenderWindow* window_, double screenWidth_, double screenHeight_, short level, Color menuColor)
	: window(window_)
	  , screenWidth(screenWidth_)
	  , screenHeight(screenHeight_)
	  , myView(sandbox, screenWidth_, screenHeight_)
	  , sandbox(level)
	  , game_state(GAME_STATE::FINISHED)
	  , regime(2)
{
	//1-random generation, 2-set positions

	Font* font = new Font();
	if (!font->loadFromFile("Fonts/Pixel.ttf"))
	{
		std::cout << "Error -> RoadMap -> couldn't load text font" << std::endl;
	}


	pause_menu = new PopUpWindow(screenWidth, screenHeight, 800, 800, window);
	pause_menu->addLabel(screenWidth, screenHeight, "Menu", font, 60, 10);
	pause_menu->addBackground(sandbox.getMapWidth(), sandbox.getMapHeight(), Color(59, 66, 73, 87));
	pause_menu->createGroupLine();

	CRect<float>* tmp = pause_menu->calculatePFNG(100, 100, 0);
	Group* t0 = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
	delete tmp;
	
	t0->createElementLine();
	t0->addButton(40, font, "CONTINUE", menuColor, 0, 0);
	
	t0->createElementLine();
	t0->addButton(40, font, "SETTINGS", menuColor, 1, 1);

	t0->createElementLine();
	t0->addButton(40, font, "BACK TO LOBBY", menuColor, 2, 2);

	t0->setAlignment("center auto", "center 50");
	pause_menu->addCallback(t0->getButtonState(0), (short)BUTTON_STATE::BTN_ACTIVE, 0, &Level::continueGame , this);
	
	pause_menu->addCallback(t0->getButtonState(2), (short)BUTTON_STATE::BTN_ACTIVE, 0, &Level::finishGame, this);
	pause_menu->addGroup(t0, 0);


	life_bar = new ScaleParametrBar();

	initPlayer();
		menu_timer.restart();
		if(regime == -1)
		{
			//initEvilBall();
			//init_Kusaka();
			//init_chubacabra();
			//init_Wolf_boss();
			initWeapons();
		}else if(level == 4)
		{
			//init_enemy();
			initWeapons();
		}
	
}

Level::~Level()
{
	delete player;
	
	delete life_bar;
	/*delete evil_Ball;
	for (auto& enemy : *evil_ball_vector)
	{
		delete enemy;
	}
	evil_ball_vector->clear();
	for (auto& enemy : *Kusaka_vector)
	{
		delete enemy;
	}
	Kusaka_vector->clear();*/
	/*for (auto& enemy : *Red_Mutant_vector_)
	{
		delete enemy;
	}
	Red_Mutant_vector_->clear();*/
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
	evil_ball_vector = new vector<EyeEvil*>();
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
	Red_Mutant_vector_ = new vector<RedMutant*>();
	for (int i = 0; i < num_of_enemy_; i++)
	{
		RedMutant* enemy = new RedMutant(sandbox, player->getGeneralInfo());
		Red_Mutant_vector_->push_back(enemy);
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

void Level::init_BushKiller()
{
	bush_killers_vector = new vector<BushKiller*>();
	for (int i = 0; i < num_of_enemy_; i++)
	{
		auto* enemy = new BushKiller(sandbox, player->getGeneralInfo());
		bush_killers_vector->push_back(enemy);
	}
}


void Level::init_enemy()
{
	//Kusaka_vector = new vector<kusaka*>();
	//evil_ball_vector = new vector<EyeEvil*>();
	//Red_Mutant_vector_ = new vector<RedMutant*>();
	//boss_vector = new vector<WolfBoss*>();
	//bush_killers_vector = new vector<BushKiller*>();
	//hornet_vector = new vector<hornet*>();
	//hornet_hives_vector = new vector<HornetHive*>();

	//evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo()));
	//evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo()));
	//evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo()));
	//evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo()));
	//boss_vector->push_back(new WolfBoss(sandbox, player->getGeneralInfo()));
	//hornet_hives_vector->push_back(new HornetHive(sandbox, player->getGeneralInfo()));

	//bush_killers_vector->push_back(new BushKiller(sandbox, player->getGeneralInfo()));
	//Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	//Red_Mutant_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));
	//Red_Mutant_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));
	//Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	///Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	//Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	//Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	//Red_Mutant_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));
	//Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	//evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo()));
	//evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo()));
	//Kusaka_vector->push_back(new kusaka(sandbox, player->getGeneralInfo()));
	//Red_Mutant_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));
	//Red_Mutant_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));
	//Red_Mutant_vector_->push_back(new RedMutant(sandbox, player->getGeneralInfo()));
}

	
	
	

void Level::updateEvilBall()
{
	auto it = evil_ball_vector->begin();
	while (it != evil_ball_vector->end())
	{
		(*it)->update();

		if ((*it)->eye_state == EYE_EVIL_STATE::DEATH && (*it)->DEATH_timer.getElapsedTime().asSeconds() >= 5.1f)
		{
			delete*it;
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

		if ((*it)->kusaka_state == KUSAKA_STATE::KUSAKA_DEATH && (*it)->DEATH_timer.getElapsedTime().asSeconds() >=
			5.1f)
		{
			delete*it;
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

void Level::update_BushKiller()

{
	for (auto& enemy : *bush_killers_vector)

	{
		enemy->update();
	}

	//auto it = bush_killers_vector->begin();
	//while (it != bush_killers_vector->end())
	//{
	//	(*it)->update();

	//	if ((*it)->kusaka_state == KUSAKA_STATE::KUSAKA_DEATH && (*it)->DEATH_timer.getElapsedTime().asSeconds() >= 5.1f)
	//	{
	//		delete* it;
	//		it = bush_killers_vector->erase(it);
	//	}
	//	else
	//	{
	//		++it;
	//	}
	//}
}

void Level::update_Red_Mutant()
{
	auto it = Red_Mutant_vector_->begin();
	while (it != Red_Mutant_vector_->end())
	{
		(*it)->update();

		if ((*it)->red_mutant_state == RED_MUTANT_STATE::RED_MUTANT_DEATH && (*it)->DEATH_timer.getElapsedTime().
			asSeconds() >= 5.1f)
		{
			delete *it;
			it = Red_Mutant_vector_->erase(it);
		}
		else
		{
			++it;
		}
	}
	//for (auto& enemy : *Red_Mutant_vector_)
	//{
	//	enemy->update();
	//	//(*Red_Mutant_vector_)[i]->update();
	//}
}

void Level::update_Wolf_boss()
{
	for (auto& enemy : *boss_vector)

	{
		enemy->update();
	}
}

	void Level::updateGameMenu(){
		pause_menu->update(myView.getCurrentViewCords());
	}


void Level::updateGameState()
{
	if (menu_timer.getElapsedTime().asSeconds() >= 0.2f)
	{
		if (Keyboard::isKeyPressed(Keyboard::BackSpace))
		{
			if (game_state == GAME_STATE::PAUSED)
			{
				game_state = GAME_STATE::CONTINUES;
			}
			else
			{
				game_state = GAME_STATE::PAUSED;
			}
			menu_timer.restart();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			game_state = GAME_STATE::FINISHED;
		}
	}
}

void Level::updateMap()
{
	sandbox.update(*window, myView.getCurrentViewCords());
}

void Level::updateLifeBar()
{
	life_bar->updateScaleWidth(player->getHP());
	life_bar->update(myView.getCurrentViewCords(), screenWidth, screenHeight);
}

void Level::initPlayer()
{
	player = new Player(sandbox);
}

void Level::initView()
{
}

void Level::update()
{
	updatePlayer();

		/*updateEvilBall();
		update_Kusaka();*/
		updateView();
		updateCursor();
		updateMap();
		updateLifeBar();
	
	//update_Enemy();
	//update_Red_Mutant();
	//update_Wolf_boss();
	//update_BushKiller();
	updateCursor();
}

	
void Level::updateEvents()
{
	while (window->pollEvent(event))
	{
		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::D)
			{
				player->resetAnimationTimer();
			}
			if (event.key.code == Keyboard::A)
			{
				player->resetAnimationTimer();
			}
			if (event.key.code == Keyboard::W)
			{
				player->resetAnimationTimer();
				player->resetIsFlying();
			}
			if (event.key.code == Keyboard::S)
			{
				player->resetAnimationTimer();
			}
			if (event.key.code == Keyboard::Space)
			{
				player->resetAnimationTimer();
				player->resetNTHJump();
			}
		}
		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta > 0)
			{
				player->change_weapon(1);
				//player->changeHP(-1);
			}
			else
			{
				player->change_weapon(-1);
			}
		}
	}
}

void Level::updateView()
{
	myView.updateView(player->getGlobalBounds());
}

	
	
	void Level::renderGameMenu(){
		pause_menu->render();
	}
void Level::updateCursor()
{
	//sf::Vector2f p(sf::Mouse::getPosition(window));
	//cursor->update(sf::Vector2f(sf::Mouse::getPosition(window)));
	//std::cout << p.x << "  " << p.y<< std::endl;
}

void Level::update_Enemy()
{
	
	auto it = hornet_vector->begin();
	while (it != hornet_vector->end())
	{
		(*it)->update();

		if ((*it)->hornet_state == HORNET_STATE::DEATH && (*it)->DEATH_timer.getElapsedTime().asSeconds() >= 10.1f)
		{
			delete*it;
			it = hornet_vector->erase(it);
		}
		else
		{
			++it;
		}
	}

	auto it1 = hornet_hives_vector->begin();
	while (it1 != hornet_hives_vector->end())
	{
		(*it1)->update();
		if((*it1)->hornet_state == HORNET_HIVE_STATE::DEATH && (*it1)->cout_hornet>0)
		{
			(*it1)->cout_hornet = 0;
			hornet_vector->push_back(new hornet(sandbox, player->getGeneralInfo()));
			hornet_vector->push_back(new hornet(sandbox, player->getGeneralInfo()));
			hornet_vector->push_back(new hornet(sandbox, player->getGeneralInfo()));


		}
		if ((*it1)->hornet_state == HORNET_HIVE_STATE::DEATH && (*it1)->DEATH_timer.getElapsedTime().asSeconds() >= 4.1f)
		{
			delete* it1;
			it1 = hornet_hives_vector->erase(it1);
		}
		else
		{
			++it1;
		}
	}

	
}


void Level::renderPLayer()
{
	player->render(*window);
}

void Level::renderMap()
{
	sandbox.background_render(*window, myView.getCurrentViewCords());
	sandbox.first_render(*window, myView.getCurrentViewCords());
}

void Level::renderCursor()
{
	//cursor->render(window);
}

void Level::updatePlayer()
{
	player->update(window, myView.getCurrentViewCords());
}

void Level::render()
{
	window->clear(Color::White);

	renderMap();
	renderPLayer();
	//renderEnemy();
	//renderEvilBall();
	//render_Kusaka();
	//render_chubacabra();
	//render_BushKiller();
	//render_shot();
	//render_Wolf_boss();

	sandbox.second_render(*window, myView.getCurrentViewCords());
	renderCursor();
	window->setView(myView.view);

	renderLifeBar();

	if (game_state == GAME_STATE::PAUSED)
	{
		updateGameMenu();
		renderGameMenu();
	}
	window->display();
}

void Level::renderEnemy()
{
	for (auto& enemy : *hornet_vector)

	{
		enemy->render(*window);
	}

	for (auto& enemy : *hornet_hives_vector)

	{
		enemy->render(*window);
	}
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
	for (auto& enemy : *Red_Mutant_vector_)
	{
		//(*Red_Mutant_vector_)[i]->render(*window);
		enemy->render(*window);
	}
}

void Level::render_BushKiller()
{
	for (auto& enemy : *bush_killers_vector)
	{
		//(*boss_vector)[i]->render(*window);
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
	for (auto& enemy : *bush_killers_vector)
	{
		//if ((*evil_ball_vector)[i]->laser_existence())
		if (!enemy->leaf_empty())
		{
			//(*evil_ball_vector)[i]->draw_laser(1, *window);
			enemy->draw_leaf(*window);
		}
	}
}

void Level::renderLifeBar()
{
	life_bar->render(window);
}

	
void Level::start()
{
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	//	int y = 0;
	//}
	game_state = GAME_STATE::CONTINUES;
	while (game_state != GAME_STATE::FINISHED)
	{
		updateGameState();
		updateEvents();
		//this bug has a beneficial effect
		if (game_state != GAME_STATE::PAUSED)
		{
			update();
		}
		render();
	}
}

void Level::initWeapons()
{
	player->initWeapon({
			reinterpret_cast<vector<Enemy*>*>(Kusaka_vector), reinterpret_cast<vector<Enemy*>*>(evil_ball_vector),
			reinterpret_cast<vector<Enemy*>*>(Red_Mutant_vector_), reinterpret_cast<vector<Enemy*>*>(boss_vector),
			reinterpret_cast<vector<Enemy*>*>(bush_killers_vector),
			reinterpret_cast<vector<Enemy*>*>(hornet_vector),
			reinterpret_cast<vector<Enemy*>*>(hornet_hives_vector)
		}
	);
}
