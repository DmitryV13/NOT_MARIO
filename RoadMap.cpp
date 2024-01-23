#include "stdafx.h"
#include "RoadMap.h"

	RoadMap::RoadMap(RenderWindow* window_, double screen_w, double screen_h, Color menuColor_, TextureManager* t_manager_)
		: window(window_), screen_height(screen_h), screen_width(screen_w), menuColor(menuColor_), t_manager(t_manager_){
		state = PAGE_STATE::PAGE_CLOSED;
		cb_handler = new CallbacksHandler();
		inventory = new Inventory();
		initFont();
		initBackground();
		menu_timer.restart();
		
		level_selection = new PopUpWindow(screen_width, screen_height, 800, 800, window);
		shop = new PopUpWindow(screen_width, screen_height, 1000, 800, window);
		all_static_items = new Group(screen_width, screen_height, Vector2f(0, 0));
		///////////////////////////////////////////////////////////////////////////
		all_static_items->createElementLine();
		CRect<float>* tmp = all_static_items->calculatePFNII(100, 15, 0);
		Group* t0 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;
		all_static_items->addIElement((InterfaceItem*)t0, 0);
		
		t0->createElementLine();
		tmp = t0->calculatePFNII(20, 100, 0);
		Group* t01 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;
		t0->addIElement((InterfaceItem*)t01, 0);

		t01->createElementLine();
		t01->addButton(240, 80, 40, font, "SHOP", Color::White, Color::White, Color(14, 178, 12, 255), Color(14, 178, 12, 255), true, 10, 0);
		cb_handler->addCallback(t01->getButtonState(10), BUTTON_STATE::BTN_ACTIVE, 0, &PopUpWindow::setPUWStateO, shop);

		tmp = t0->calculatePFNII(60, 100, 0);
		Group* t02 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;
		t0->addIElement((InterfaceItem*)t02, 0);

		t02->createElementLine();
		tmp = t02->calculatePFNII(5, 100, 0);
		ResourceInfo* ri0 = new ResourceInfo(tmp->first, tmp->second, inventory->getItemInfo("Coin").first,
			inventory->getItemInfo("Coin").second, 30, font, t_manager, 0, "Coin", false);
		t02->addIElement((InterfaceItem*)ri0, 0);
		delete tmp;

		tmp = t02->calculatePFNII(5, 100, 0);
		ResourceInfo* ri1 = new ResourceInfo(tmp->first, tmp->second, inventory->getItemInfo("BSplinter").first,
			inventory->getItemInfo("BSplinter").second, 30, font, t_manager, 0, "BSplinter", false);
		t02->addIElement((InterfaceItem*)ri1, 0);
		delete tmp;
		
		tmp = t02->calculatePFNII(5, 100, 0);
		ResourceInfo* ri2 = new ResourceInfo(tmp->first, tmp->second, inventory->getItemInfo("RSplinter").first,
			inventory->getItemInfo("RSplinter").second, 30, font, t_manager, 0, "RSplinter", false);
		t02->addIElement((InterfaceItem*)ri2, 0);
		delete tmp;

		tmp = t0->calculatePFNII(20, 100, 0);
		Group* t03 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;
		t0->addIElement((InterfaceItem*)t03, 0);
		
		t03->createElementLine();
		t03->addButton(80, 80, 40, font, "", menuColor, Color::White, Color(108, 82, 59, 255)
			, Color(163, 118, 76, 255), t_manager, 0, "ArrowBack", true, 9, 0);
		cb_handler->addCallback(t03->getButtonState(9), BUTTON_STATE::BTN_ACTIVE, 0, &RoadMap::closeRoadMap, this);
		
		t01->setAlignment("left 30", "center 0");
		t02->setAlignment("center 160", "center 0");
		t03->setAlignment("right 30", "center 0");
		t0->setAlignment("space between 0", "top 0");
		///////////////////////////////////////////////////////////////////////////
		all_static_items->createElementLine();
		tmp = all_static_items->calculatePFNII(100, 50, 0);
		Group* t1 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;
		all_static_items->addIElement((InterfaceItem*)t1, 1);
		
		t1->createElementLine();
		tmp = t1->calculatePFNII(30, 100, 0);
		Reviewer* r0 = new Reviewer(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;
		t1->addButton(100, 100, 40, font, "", menuColor, Color::White, Color(239, 135, 6, 255)
			, Color(255, 185, 12), t_manager, 0, "ArrowL", true, 0, 0);
		cb_handler->addCallback(t1->getButtonState(0), BUTTON_STATE::BTN_ACTIVE, -1, &Reviewer::changeCurrentImage, r0);
		t1->addIElement((InterfaceItem*)r0, 0);
		t1->addButton(100, 100, 40, font, "", menuColor, Color::White, Color(239, 135, 6, 255)
			, Color(255, 185, 12), t_manager, 0, "ArrowR", true, 1, 0);
		cb_handler->addCallback(t1->getButtonState(1), BUTTON_STATE::BTN_ACTIVE, 1, &Reviewer::changeCurrentImage, r0);
		//tmp = t0->calculatePFNII(5, 100, 0);

		//ResourceInfo* ri0 = new ResourceInfo(tmp->first, tmp->second, (int*)u, 700, 20, font, t_manager, 0, "Coin");
		//t0->addIElement((InterfaceItem*)ri0, 0);
		r0->addAnimatedImage(t_manager, 4, "Hero1", IntRect(0, 0, 54, 70), 6);
		r0->addAnimatedImage(t_manager, 4, "Hero2", IntRect(0, 0, 63, 68), 1);
		t1->setAlignment("center 0", "center 0");

		
		/////////////////////////////////////////////////////////////////////////////
		all_static_items->createElementLine();
		tmp= all_static_items->calculatePFNII(100, 20, 0);
		Group* t2 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;
		all_static_items->addIElement((InterfaceItem*)t2, 2);

		t2->createElementLine();
		t2->addButton(400, 120, 40, font, "INVENTORY", Color::White, Color::White, Color(212, 24, 22, 255), Color(212, 24, 22, 255), true, 2, 0);
		t2->addButton(400, 120, 40, font, "PLAY", Color::White, Color::White, Color(43, 95, 194, 255), Color(43, 95, 194, 255), true, 3, 0);
		cb_handler->addCallback(t2->getButtonState(3), BUTTON_STATE::BTN_ACTIVE, 0, &PopUpWindow::setPUWStateO, level_selection);
		t2->setAlignment("space between 200", "center 0");

		all_static_items->setAlignment("center 0", "bottom 0");
		t0->changePositionY(-120);
		///////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////
		level_selection->addBackground(screen_width, screen_height, Color(59, 66, 73, 87));
		level_selection->createGroupLine();
		tmp = level_selection->calculatePFNG(100, 100, 0);
		Group* l0= new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;

		l0->addGroupName("Select level", 50, font);
		l0->createElementLine();
		tmp = l0->calculatePFNII(100, 30, 0);
		Group* l1=new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;

		l0->addIElement((InterfaceItem*)l1, 0);
		l1->addGroupName("Static levels", 30, font);
		l1->createElementLine();
		l1->addButton(100, 100, 40, font, "1", menuColor, Color::White, Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 4, 0);
		level_selection->addCallback(l1->getButtonState(4), BUTTON_STATE::BTN_ACTIVE, 4, &RoadMap::openLevel, this);
		l1->setAlignment("center 20", "center 0");
		///////////////////////////////////////////////////////////////////////////
		l0->createElementLine();
		tmp = l0->calculatePFNII(100, 30, 0);
		Group* l2 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;

		l0->addIElement((InterfaceItem*)l2, 1);
		l2->addGroupName("Infinite levels", 30, font);
		l2->createElementLine();
		l2->addButton(100, 100, 40, font, "1", menuColor, Color::White, Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 5, 0);
		l2->addButton(100, 100, 40, font, "2", menuColor, Color::White, Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 6, 0);
		l2->addButton(100, 100, 40, font, "3", menuColor, Color::White, Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 7, 0);
		level_selection->addCallback(l2->getButtonState(5), BUTTON_STATE::BTN_ACTIVE, 1, &RoadMap::openLevel, this);
		level_selection->addCallback(l2->getButtonState(6), BUTTON_STATE::BTN_ACTIVE, 2, &RoadMap::openLevel, this);
		level_selection->addCallback(l2->getButtonState(7), BUTTON_STATE::BTN_ACTIVE, 3, &RoadMap::openLevel, this);
		l2->setAlignment("center 20", "center 0");
		///////////////////////////////////////////////////////////////////////////
		l0->createElementLine();
		tmp = l0->calculatePFNII(100, 30, 0);
		Group* l3 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;

		l0->addIElement((InterfaceItem*)l3, 2);
		l3->createElementLine();
		l3->addButton(300, 100, 40, font, "CLOSE", menuColor, Color::White, Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 8, 0);
		level_selection->addCallback(l3->getButtonState(8), BUTTON_STATE::BTN_ACTIVE, 0, &PopUpWindow::setPUWStateC, level_selection);
		l3->setAlignment("center 0", "bottom 0");

		l0->setAlignment("center 0", "space around 0");
		level_selection->addGroup(l0, 0);
		///////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////
		shop->addLabel(screen_width, screen_height, "Shop", font, 60, 10);
		shop->addBackground(screen_width, screen_height, Color(59, 66, 73, 87));
		shop->createGroupLine();

		tmp = shop->calculatePFNG(100, 100, 0);
		Group* sh0 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;
		shop->addGroup(sh0, 0);

		sh0->createElementLine();
		tmp = sh0->calculatePFNII(85, 100, 0);
		TabContainer* tc0 = new TabContainer(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
		sh0->addIElement((InterfaceItem*)tc0, 0);
		
		///////////////////////////////////////////////////////////////////////////
		Group* tb0 = new Group(tc0->getGlobalBounds().width, tc0->getGlobalBounds().height,
			Vector2f(tc0->getGlobalBounds().left, tc0->getGlobalBounds().top));
		tc0->addTab(tb0);
		tb0->createElementLine();

		tmp = tb0->calculatePFNII(30, 48, 0);
		Group* tb01=new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		ProductCard* prc0 = new ProductCard(5, 2, inventory->getItemInfo("Arrow").first);
		prc0->setGroup(tb01, Color(61, 85, 132, 255));
		prc0->setCurrency(inventory->getItemInfo("Coin").first);
		tb0->addIElement((InterfaceItem*)prc0, 0);
		delete tmp;

		tb01->createElementLine();
		tmp = tb01->calculatePFNII(85, 55, 0);
		Group* tb001 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		tb01->addIElement((InterfaceItem*)tb001, 0);
		delete tmp;

		tb001->createElementLine();
		tmp = tb001->calculatePFNII(100, 100, 0);
		Reviewer* r1 = new Reviewer(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		r1->addAnimatedImage(t_manager, 0, "Arrow1", IntRect(0, 0, 40, 5), 1);
		tb001->addIElement((InterfaceItem*)r1, 0);
		tb001->setBColor(Color(173, 173, 173, 255));
		delete tmp;

		tb01->createElementLine();
		tmp = tb01->calculatePFNII(85, 10, 0);
		ResourceInfo* ii0 = new ResourceInfo(tmp->first, tmp->second, prc0->getPrice(), 0, 24, font, t_manager, 0, "Coin", true);
		tb01->addIElement((InterfaceItem*)ii0, 1);
		delete tmp;

		tmp = tb01->calculatePFNII(85, 20, 0);
		tb01->createElementLine();
		tb01->addButton(tmp->third, tmp->fourth-1, 30, font, "BUY", Color::White, Color::White, Color(239, 135, 6, 255), Color(239, 135, 6, 255), false, 14, 2);
		shop->addCallback(tb01->getButtonState(14), BUTTON_STATE::BTN_ACTIVE, 0, &ProductCard::buy, prc0);
		//shop->addCallback(prc0->getPurchaseState(), PURCHASE::PURCHASE_DONE, 0, &ImageInfo::setText, ii0);
		delete tmp;

		prc0->setAlignment("center 0", "space around");
		tb0->setAlignment("left 10", "top 10");
		///////////////////////////////////////////////////////////////////////////
		Group* tb1 = new Group(tc0->getGlobalBounds().width, tc0->getGlobalBounds().height,
			Vector2f(tc0->getGlobalBounds().left, tc0->getGlobalBounds().top));
		tc0->addTab(tb1);
		tb1->createElementLine();

		tb1->addButton(300, 60, 20, font, "UPGRADE", menuColor, Color::White, Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 5, 0);

		///////////////////////////////////////////////////////////////////////////
		tmp = sh0->calculatePFNII(15, 100, 0);
		Group* btn0 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		sh0->addIElement((InterfaceItem*)btn0, 0);

		btn0->createElementLine();
		btn0->addButton(tmp->third, 60, 20, font, "BUY", menuColor, Color::White, Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 11, 0);
		shop->addCallback(btn0->getButtonState(11), BUTTON_STATE::BTN_ACTIVE, 0, &TabContainer::changeCurrentTab, tc0);
		btn0->createElementLine();
		btn0->addButton(tmp->third, 60, 20, font, "UPGRADE", menuColor, Color::White, Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 12, 1);
		shop->addCallback(btn0->getButtonState(12), BUTTON_STATE::BTN_ACTIVE, 1, &TabContainer::changeCurrentTab, tc0);
		btn0->createElementLine();
		btn0->addButton(tmp->third, 60, 20, font, "CLOSE", menuColor, Color::White, Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 13, 2);
		shop->addCallback(btn0->getButtonState(13), BUTTON_STATE::BTN_ACTIVE, 0, &PopUpWindow::setPUWStateC, shop);
		btn0->setAlignment("center 0", "top 5");
		delete tmp;
	}

	void RoadMap::initFont(){
		font = new Font();
		if (!font->loadFromFile("Fonts/Pixel.ttf")) {
			std::cout << "Error -> RoadMap -> couldn't load text font" << std::endl;
		}
	}

	void RoadMap::initBackground(){
		background.setTexture(t_manager->getTexture(0, "LobbyBackground"));
		background.setScale(static_cast<float>(window->getSize().y) / background.getLocalBounds().height, static_cast<float>(window->getSize().y) / background.getLocalBounds().height);
		background.setPosition((static_cast<float>(window->getSize().x) - background.getGlobalBounds().width) / 2, 0);
		//background.setColor(Color(180, 180, 180, 255));
	}

	void RoadMap::updateMenuState(){
		if (menu_timer.getElapsedTime().asSeconds() >= 0.2f) {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				state = PAGE_STATE::PAGE_CLOSED;
			}
			menu_timer.restart();
		}
	}

	void RoadMap::updateEvents(){
		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				window->close();
			}
		}
	}

	void RoadMap::update(){
		window->setView(View(FloatRect(0, 0, screen_width, screen_height)));

		if (level_selection->getState() == POP_UP_WINDOW_STATE::PUW_CLOSED &&
			shop->getState() == POP_UP_WINDOW_STATE::PUW_CLOSED) {
			all_static_items->update(Vector2f(Mouse::getPosition(*window)), FloatRect(window->getView().getCenter(), Vector2f(screen_width, screen_height)));
		}
		cb_handler->update();

		window->setView(View(FloatRect(0, 0, screen_width, screen_height)));
		updateEvents();
	}

	void RoadMap::openLevel(float level_index){
		Level* level = new Level(window, screen_width, screen_height, static_cast<int>(level_index), menuColor);
		level->start();
		delete level;
		menu_timer.restart();
		level_selection->setPUWStateC(0);
	}

	void RoadMap::closeRoadMap(float q){
		state = PAGE_STATE::PAGE_CLOSED;
	}

	void RoadMap::render(){
		window->clear();
		window->draw(background);

		all_static_items->render(window);
		if (level_selection->getState() == POP_UP_WINDOW_STATE::PUW_OPENED) {
			level_selection->update(FloatRect(window->getView().getCenter(), Vector2f(screen_width, screen_height)));
			level_selection->render();
		}
		if (shop->getState() == POP_UP_WINDOW_STATE::PUW_OPENED) {
			shop->update(FloatRect(window->getView().getCenter(), Vector2f(screen_width, screen_height)));
			shop->render();
		}
		window->display();
	}

	void RoadMap::enter(RenderWindow* window_){
		state = PAGE_STATE::PAGE_OPENED;
		while (state == PAGE_STATE::PAGE_OPENED) {
			updateMenuState();
			update();
			render();
		}
	}