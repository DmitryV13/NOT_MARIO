#include "stdafx.h"
#include "Level.h"

	Level::Level(RenderWindow* window_, double screenWidth_, double screenHeight_, short level, Color menuColor,
	             TextureManager* t_manager_, Warehouse* warehouse_, short regime_)
		: window(window_)
		, t_manager(t_manager_)
		, warehouse(warehouse_)
		, screenWidth(screenWidth_)
		, screenHeight(screenHeight_)
		, myView(sandbox, screenWidth_, screenHeight_)
		, sandbox(level)
		, game_state(GAME_STATE::FINISHED)
		, regime(regime_)
		, object_available(false){
		//-1-random generation, 2-set positions
		Font* font = new Font();
		if (!font->loadFromFile("Fonts/Pixel.ttf"))
		{
			std::cout << "Error -> RoadMap -> couldn't load text font" << std::endl;
		}
		//Chest* ooo=new Chest();
		//
		//auto df = sandbox.getObjects();
		//for (int i = 0; i < df.size(); i++) {
		//	if (df[i]->getOType() == OBJECT_TYPE::CHEST) {
		//		ooo = (Chest*)(df[i]);
		//		break;
		//	}
		//}
	
		all_static_items = new Group(0, 0, screenWidth, screenHeight);
		pause_menu = new PopUpWindow(screenWidth, screenHeight, 800, 800, window);
		level_inventory = new PopUpWindow(screenWidth, screenHeight, 600, 1000, window);
		chest_items = new PopUpWindow(screenWidth, screenHeight, 600, 500, window);
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		pause_menu->addLabel(screenWidth, screenHeight, "Menu", font, 60, 10);
		pause_menu->addBackground(sandbox.getMapWidth(), sandbox.getMapHeight(), Color(59, 66, 73, 87));
		pause_menu->createGroupLine();
	
		CRect<float>* tmp = pause_menu->calculatePFNG(100, 100, 0);
		Group* pm = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
	
		pm->createElementLine();
		pm->addButton(40, font, "CONTINUE", menuColor, 0, 0);
	
		pm->createElementLine();
		pm->addButton(40, font, "SETTINGS", menuColor, 1, 1);
	
		pm->createElementLine();
		pm->addButton(40, font, "BACK TO LOBBY", menuColor, 2, 2);
	
		pm->setAlignment("center auto", "center 50");
		pause_menu->addCallback(pm->getButtonState(0), (short)BUTTON_STATE::BTN_ACTIVE, 0, &Level::continueGame, this);
	
		pause_menu->addCallback(pm->getButtonState(2), (short)BUTTON_STATE::BTN_ACTIVE, 0, &Level::finishGame, this);
		pause_menu->addGroup(pm, 0);
	
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
	
		chest_items->addLabel(screenWidth, screenHeight, "Chest", font, 40, 10);
		chest_items->addBackground(sandbox.getMapWidth(), sandbox.getMapHeight(), Color(59, 66, 73, 87));
		chest_items->createGroupLine();
	
		tmp = chest_items->calculatePFNG(100, 100, 0);
		Group* ci = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
		chest_items->addGroup(ci, 0);
	
		ci->createElementLine();
		tmp = ci->calculatePFNII(100, 70, 0);
		Group* ci_f0_top = new Form(tmp->first, tmp->second, tmp->third, tmp->fourth);
		form = (Form*)ci_f0_top;
		delete tmp;
		ci->addIElement((InterfaceItem*)ci_f0_top, 0);
	
		for (int in = 0; in < 2; in++) {
			ci_f0_top->createElementLine();
			for (int jn = 0; jn < 4; jn++) {
				tmp = ci_f0_top->calculatePFNII(22, 45, in);
				CheckboxItem* temp = new CheckboxItem(tmp->first, tmp->second, tmp->third, tmp->fourth, 15, font);
				temp->setBColor(Color(118, 118, 118, 255));
				delete tmp;
				ci_f0_top->addIElement((InterfaceItem*)temp, in);
			}
		}
	
		ci_f0_top->setAlignment("space around", "space around");
	
		ci->createElementLine();
		tmp = ci->calculatePFNII(100, 20, 0);
		Group* ci_g1_bottom = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
		ci->addIElement((InterfaceItem*)ci_g1_bottom, 1);
	
		ci_g1_bottom->createElementLine();
		tmp = ci_g1_bottom->calculatePFNII(30, 70, 0);
		ci_g1_bottom->addButton(tmp->third, tmp->fourth, 20, font, "TAKE", Color::White, Color::White,
			Color(239, 135, 6, 255), Color(239, 155, 6, 255), false, 0, 0);
		chest_items->addCallback(ci_g1_bottom->getButtonState(0), BUTTON_STATE::BTN_ACTIVE, 0,
			&Form::activateForm, (Form*)ci_f0_top);
		ci_g1_bottom->addButton(tmp->third, tmp->fourth, 20, font, "CLOSE", Color::White, Color::White,
			Color(212, 24, 22, 255), Color(212, 24, 22, 255), false, 1, 0);
		chest_items->addCallback(ci_g1_bottom->getButtonState(1), BUTTON_STATE::BTN_ACTIVE, 0,
			&PopUpWindow::setPUWStateC, chest_items);
	
		ci_g1_bottom->setAlignment("space around", "center 0");
		ci->setAlignment("center 0", "space between 10");

		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////

		initPlayer(level);

		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
	
		all_static_items->createElementLine();
		tmp = all_static_items->calculatePFNII(20, 30, 0);
		Group* asi_g0_left = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		all_static_items->addIElement((InterfaceItem*)asi_g0_left, 0);
		delete tmp;

		asi_g0_left->createElementLine();
		tmp = asi_g0_left->calculatePFNII(100, 15, 0);
		ScaleParameterBar* asi_spb_top = new ScaleParameterBar(tmp->first, tmp->second, tmp->third, tmp->fourth,
			player->getGeneralInfo()->getHp(), player->getGeneralInfo()->getMaxHP(), t_manager, warehouse,
			"RedScaleBar");
		delete tmp;
		asi_g0_left->addIElement((InterfaceItem*)asi_spb_top, 0);

		asi_g0_left->createElementLine();
		tmp = asi_g0_left->calculatePFNII(90, 15, 0);
		ScaleParameterBar* asi_spb_bottom = new ScaleParameterBar(tmp->first, tmp->second, tmp->third, tmp->fourth,
			player->getGeneralInfo()->getMana(), player->getGeneralInfo()->getMaxMana(), t_manager, warehouse,
			"BlueScaleBar");
		delete tmp;
		asi_g0_left->addIElement((InterfaceItem*)asi_spb_bottom, 1);

		asi_g0_left->setAlignment("left 0", "top 0");
		all_static_items->setAlignment("left 10", "top 10");
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		life_bar = new ScaleParameterBar();
	
		
		menu_timer.restart();
		if (regime == -1)
		{
			random_init_enemy();
		}
		else if (level == 4)
		{
			init_enemy();
		}
		initWeapons();
	}
	
	Level::~Level()
	{
		delete player;
	
		delete life_bar;
	
		if (hornet_vector != nullptr)
		{
			for (auto& enemy : *hornet_vector)
			{
				delete enemy;
			}
			hornet_vector->clear();
			delete hornet_vector;
	
			//boss_vector->clear();
		}
	
	
		if (hornet_hives_vector != nullptr)
		{
			for (auto& enemy : *hornet_hives_vector)
			{
				delete enemy;
			}
			hornet_hives_vector->clear();
			delete hornet_hives_vector;
		}
	
		if (evil_ball_vector != nullptr)
		{
			for (auto& enemy : *evil_ball_vector)
			{
				delete enemy;
			}
			evil_ball_vector->clear();
			delete evil_ball_vector;
		}
	
		if (Kusaka_vector != nullptr)
		{
			for (auto& enemy : *Kusaka_vector)
			{
				delete enemy;
			}
			Kusaka_vector->clear();
			delete Kusaka_vector;
		}
	
		if (Red_Mutant_vector_ != nullptr)
		{
			for (auto& enemy : *Red_Mutant_vector_)
			{
				delete enemy;
			}
			Red_Mutant_vector_->clear();
			delete Red_Mutant_vector_;
		}
	
		if (bush_killers_vector != nullptr)
		{
			for (auto& enemy : *bush_killers_vector)
			{
				delete enemy;
			}
			bush_killers_vector->clear();
			delete bush_killers_vector;
		}
	
		if (boss_vector != nullptr)
		{
			for (auto& enemy : *boss_vector)
			{
				delete enemy;
			}
			boss_vector->clear();
			delete boss_vector;
		}
	}
	
	void Level::finishGame(float q)
	{
		game_state = GAME_STATE::FINISHED;
	}
	
	void Level::continueGame(float q)
	{
		game_state = GAME_STATE::CONTINUES;
	}
	
	
	void Level::init_enemy()
	{
		Kusaka_vector = new vector<kusaka*>();
		evil_ball_vector = new vector<EyeEvil*>();
		Red_Mutant_vector_ = new vector<RedMutant*>();
		boss_vector = new vector<WolfBoss*>();
		bush_killers_vector = new vector<BushKiller*>();
		hornet_vector = new vector<hornet*>();
		hornet_hives_vector = new vector<HornetHive*>();
	
		evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo(), 1));
		evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo(), 2));
		evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo(), 2));
		evil_ball_vector->push_back(new EyeEvil(sandbox, player->getGeneralInfo(), 2));
		boss_vector->push_back(new WolfBoss(sandbox, player->getGeneralInfo(), 2));
		hornet_hives_vector->push_back(new HornetHive(sandbox, player->getGeneralInfo(), 2));
	
		bush_killers_vector->push_back(new BushKiller(sandbox, player->getGeneralInfo(), 2));
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
	
	void Level::random_init_enemy()
	{
		evil_ball_vector = new vector<EyeEvil*>();
		for (int i = 0; i < num_of_enemy_; i++)
		{
			EyeEvil* enemy = new EyeEvil(sandbox, player->getGeneralInfo(), 1);
			evil_ball_vector->push_back(enemy);
		}
	
	
		Kusaka_vector = new vector<kusaka*>();
		for (int i = 0; i < num_of_enemy_; i++)
		{
			kusaka* enemy = new kusaka(sandbox, player->getGeneralInfo(), 1);
			Kusaka_vector->push_back(enemy);
		}
	
		Red_Mutant_vector_ = new vector<RedMutant*>();
		for (int i = 0; i < num_of_enemy_; i++)
		{
			RedMutant* enemy = new RedMutant(sandbox, player->getGeneralInfo(), 1);
			Red_Mutant_vector_->push_back(enemy);
		}
	
	
		/*boss_vector = new vector<WolfBoss*>();
		for (int i = 0; i < num_of_enemy_; i++)
		{
			WolfBoss* enemy = new WolfBoss(sandbox, player->getGeneralInfo(),1);
			boss_vector->push_back(enemy);
		}*/
	
	
		bush_killers_vector = new vector<BushKiller*>();
		for (int i = 0; i < num_of_enemy_; i++)
		{
			auto* enemy = new BushKiller(sandbox, player->getGeneralInfo(), 1);
			bush_killers_vector->push_back(enemy);
		}
	
	
		hornet_hives_vector = new vector<HornetHive*>();
	
		for (int i = 0; i < num_of_enemy_; i++)
		{
			hornet_hives_vector->push_back(new HornetHive(sandbox, player->getGeneralInfo(), 1));
		}
	
		hornet_vector = new vector<hornet*>();
	
		for (int i = 0; i < num_of_enemy_; i++)
		{
			hornet_vector->push_back(new hornet(sandbox, player->getGeneralInfo(), 1));
		}
	}
	
	void Level::updateGameMenu()
	{
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
	
	//void Level::updateLifeBar()
	//{
	//	life_bar->updateScaleWidth(player->getHP());
	//	life_bar->update(myView.getCurrentViewCords(), screenWidth, screenHeight);
	//}

	void Level::updateObjectsCollision(){
		auto objects = sandbox.getObjects();
		for (int i = 0; i < objects.size(); i++) {
			if (objects[i]->getGlobalBounds().intersects(player->getGlobalBounds())) {
				if (objects[i]->getOType() == OBJECT_TYPE::CHEST) {
					object_available = OBJECT_TYPE::CHEST;
					auto rt = ((Chest*)(objects[i]))->getItems();
					for (int in = 0; in < 2; in++) {
						for (int jn = 0; jn < 4; jn++) {
							int index_ = in * 4 + jn;
							((CheckboxItem*)(form->getElement(in, jn)))->clearInfo();
							if (index_ < rt.size()) {
								((CheckboxItem*)(form->getElement(in, jn)))->addItemInfo(t_manager, rt[index_]);
							}
						}
					}

					break;
				}
			}
			object_available = -1;
		}
	}
	
	void Level::initPlayer(short level)
	{
		if (level < 4)
		{
			player = new Player(sandbox);
		}
		else
		{
			player = new Player(sandbox, Vector2f(150, 2600));
		}
	}
	
	void Level::initView()
	{
	}
	
	void Level::update(){
		if (chest_items->getState() == POP_UP_WINDOW_STATE::PUW_CLOSED) {
			updatePlayer();
		}
		updateObjectsCollision();
	
		updateView();
		updateCursor();
		updateMap();
		all_static_items->update(Vector2f(Mouse::getPosition(*window)), myView.getCurrentViewCords());
		//updateLifeBar();
	
		update_Enemy();
	
		updateCursor();
	}
	
	
	void Level::updateEvents()
	{
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window->close();
			}
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
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::E) {
					if(object_available==OBJECT_TYPE::CHEST)
						chest_items->setPUWStateO(0);
				}
			}
		}
	}
	
	void Level::updateView()
	{
		myView.updateView(player->getGlobalBounds());
	}
	
	
	void Level::renderGameMenu()
	{
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
		if (hornet_vector != nullptr && !hornet_vector->empty())
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
		}
	
	
		if (hornet_hives_vector != nullptr && !hornet_hives_vector->empty())
		{
			auto it1 = hornet_hives_vector->begin();
			while (it1 != hornet_hives_vector->end())
			{
				(*it1)->update();
				if ((*it1)->hornet_state == HORNET_HIVE_STATE::DEATH && (*it1)->cout_hornet > 0)
				{
					(*it1)->cout_hornet = 0;
					hornet_vector->push_back(new hornet(sandbox, player->getGeneralInfo(), (*it1)->get_position().x + 64,
					                                    (*it1)->get_position().y - 35));
					hornet_vector->push_back(new hornet(sandbox, player->getGeneralInfo(), (*it1)->get_position().x,
					                                    (*it1)->get_position().y - 64));
					hornet_vector->push_back(new hornet(sandbox, player->getGeneralInfo(), (*it1)->get_position().x - 30,
					                                    (*it1)->get_position().y - 35));
				}
				if ((*it1)->hornet_state == HORNET_HIVE_STATE::DEATH && (*it1)->DEATH_timer.getElapsedTime().asSeconds() >=
					4.1f)
				{
					delete*it1;
					it1 = hornet_hives_vector->erase(it1);
				}
				else
				{
					++it1;
				}
			}
		}
	
		if (evil_ball_vector != nullptr && !evil_ball_vector->empty())
		{
			auto it2 = evil_ball_vector->begin();
			while (it2 != evil_ball_vector->end())
			{
				(*it2)->update();
	
				if ((*it2)->eye_state == EYE_EVIL_STATE::DEATH && (*it2)->DEATH_timer.getElapsedTime().asSeconds() >= 5.1f)
				{
					delete*it2;
					it2 = evil_ball_vector->erase(it2);
				}
				else
				{
					++it2;
				}
			}
		}
	
		if (Kusaka_vector != nullptr && !Kusaka_vector->empty())
		{
			auto it3 = Kusaka_vector->begin();
			while (it3 != Kusaka_vector->end())
			{
				(*it3)->update();
	
				if ((*it3)->kusaka_state == KUSAKA_STATE::KUSAKA_DEATH && (*it3)->DEATH_timer.getElapsedTime().asSeconds()
					>=
					5.1f)
				{
					delete*it3;
					it3 = Kusaka_vector->erase(it3);
				}
				else
				{
					++it3;
				}
			}
		}
	
		if (bush_killers_vector != nullptr && !bush_killers_vector->empty())
		{
			for (auto& enemy : *bush_killers_vector)
	
			{
				enemy->update();
			}
		}
	
	
		if (Red_Mutant_vector_ != nullptr && !Red_Mutant_vector_->empty())
		{
			auto it4 = Red_Mutant_vector_->begin();
			while (it4 != Red_Mutant_vector_->end())
			{
				(*it4)->update();
	
				if ((*it4)->red_mutant_state == RED_MUTANT_STATE::RED_MUTANT_DEATH && (*it4)->DEATH_timer.getElapsedTime().
					asSeconds() >= 5.1f)
				{
					delete*it4;
					it4 = Red_Mutant_vector_->erase(it4);
				}
				else
				{
					++it4;
				}
			}
		}
	
		if (boss_vector != nullptr && !boss_vector->empty())
		{
			for (auto& enemy : *boss_vector)
	
			{
				enemy->update();
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
		renderEnemy();
	
		sandbox.second_render(*window, myView.getCurrentViewCords());
		renderCursor();
		window->setView(myView.view);

		all_static_items->render(window);
		//renderLifeBar();
	
		if (chest_items->getState() == POP_UP_WINDOW_STATE::PUW_OPENED) {
			chest_items->update(FloatRect(window->getView().getCenter(), Vector2f(screenWidth, screenHeight)));
			chest_items->render();
		}
	
		if (game_state == GAME_STATE::PAUSED)
		{
			updateGameMenu();
			renderGameMenu();
		}
		window->display();
	}
	
	void Level::renderEnemy()
{
	if (hornet_vector != nullptr)
		for (auto& enemy : *hornet_vector)

		{
			enemy->render(*window);
		}

	if (hornet_hives_vector != nullptr)
		for (auto& enemy : *hornet_hives_vector)

		{
			enemy->render(*window);
		}

	if (evil_ball_vector != nullptr)
		for (auto& enemy : *evil_ball_vector)

		{
			enemy->render(*window);
		}

	if (Kusaka_vector != nullptr)
		for (auto& enemy : *Kusaka_vector)
		{
			enemy->render(*window);
		}

	if (Red_Mutant_vector_ != nullptr)
		for (auto& enemy : *Red_Mutant_vector_)
		{
			enemy->render(*window);
		}

	if (bush_killers_vector != nullptr)
		for (auto& enemy : *bush_killers_vector)
		{
			enemy->render(*window);
		}

	if (boss_vector != nullptr)
		for (auto& enemy : *boss_vector)
		{
			enemy->render(*window);
		}

	if (evil_ball_vector != nullptr)
		for (auto& enemy : *evil_ball_vector)
		{
			if (enemy->laser_existence())
			{
				enemy->draw_laser(1, *window);
			}
		}
	if (bush_killers_vector != nullptr)
		for (auto& enemy : *bush_killers_vector)
		{
			if (!enemy->leaf_empty())
			{
				enemy->draw_leaf(*window);
			}
		}
}
	
	
	void Level::renderLifeBar()
	{
		//life_bar->render(window);
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
		if(regime == -1)
		{
			player->initWeapon({
				reinterpret_cast<vector<Enemy*>*>(Kusaka_vector),
				reinterpret_cast<vector<Enemy*>*>(evil_ball_vector),
				reinterpret_cast<vector<Enemy*>*>(Red_Mutant_vector_),
				reinterpret_cast<vector<Enemy*>*>(bush_killers_vector),
				reinterpret_cast<vector<Enemy*>*>(hornet_vector),
				reinterpret_cast<vector<Enemy*>*>(hornet_hives_vector)
				}
			);
		}
		else 
		player->initWeapon({
				reinterpret_cast<vector<Enemy*>*>(Kusaka_vector),
				reinterpret_cast<vector<Enemy*>*>(evil_ball_vector),
				reinterpret_cast<vector<Enemy*>*>(Red_Mutant_vector_),
				reinterpret_cast<vector<Enemy*>*>(boss_vector),
				reinterpret_cast<vector<Enemy*>*>(bush_killers_vector),
				reinterpret_cast<vector<Enemy*>*>(hornet_vector),
				reinterpret_cast<vector<Enemy*>*>(hornet_hives_vector)
			}
		);
	}
	