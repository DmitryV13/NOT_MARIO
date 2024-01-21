#include "stdafx.h"
#include "RoadMap.h"

	RoadMap::RoadMap(RenderWindow* window_, double screen_w, double screen_h, Color menuColor_, TextureManager* t_manager_)
		: window(window_), screen_height(screen_h), screen_width(screen_w), menuColor(menuColor_), t_manager(t_manager_){
		state = PAGE_STATE::PAGE_CLOSED;
		cb_handler = new CallbacksHandler();
		initFont();
		initBackground();
		menu_timer.restart();

		level_selection = new PopUpWindow(screen_width, screen_height, 800, 800, window);
		all_static_items = new Group(screen_width, screen_height, Vector2f(0, 0));

		all_static_items->createElementLine();
		CRect<float>* tmp = all_static_items->calculatePFNII(100, 50, 0);
		Group* t0 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;
		all_static_items->addIElement((InterfaceItem*)t0, 0);

		t0->createElementLine();
		tmp = t0->calculatePFNII(30, 100, 0);
		Reviewer* r0 = new Reviewer(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		t0->addButton(100, 100, 40, font, "", menuColor, Color::White, Color(239, 135, 6, 255)
			, Color(255, 185, 12), t_manager, 0, "ArrowL", true, 0, 0);
		cb_handler->addCallback(t0->getButtonState(0), BUTTON_STATE::BTN_ACTIVE, -1, &Reviewer::changeCurrentImage, r0);
		t0->addIElement((InterfaceItem*)r0, 0);
		t0->addButton(100, 100, 40, font, "", menuColor, Color::White, Color(239, 135, 6, 255)
			, Color(255, 185, 12), t_manager, 0, "ArrowR", true, 1, 0);
		cb_handler->addCallback(t0->getButtonState(1), BUTTON_STATE::BTN_ACTIVE, 1, &Reviewer::changeCurrentImage, r0);

		r0->addAnimatedImage(t_manager, 4, "Hero1", IntRect(0, 0, 54, 70), 6);
		r0->addAnimatedImage(t_manager, 0, "B", IntRect(0, 0, 50, 50), 1);
		t0->setAlignment("center 0", "center 0");
		/////////////////////////////////////////////////////////////////////////////
		all_static_items->createElementLine();
		tmp= all_static_items->calculatePFNII(100, 20, 0);
		Group* t1 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;
		all_static_items->addIElement((InterfaceItem*)t1, 1);

		t1->createElementLine();
		t1->addButton(400, 120, 40, font, "INVENTORY", Color::White, Color::White, Color(212, 24, 22, 255), Color(212, 24, 22, 255), true, 2, 0);
		t1->addButton(400, 120, 40, font, "PLAY", Color::White, Color::White, Color(43, 95, 194, 255), Color(43, 95, 194, 255), true, 3, 0);
		cb_handler->addCallback(t1->getButtonState(3), BUTTON_STATE::BTN_ACTIVE, 0, &PopUpWindow::setPUWStateO, level_selection);
		t1->setAlignment("space between 200", "center 0");

		all_static_items->setAlignment("center 0", "bottom 0");

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
		cb_handler->addCallback(l1->getButtonState(4), BUTTON_STATE::BTN_ACTIVE, 4, &RoadMap::openLevel, this);
		l1->setAlignment("center 20", "center 0");

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
		cb_handler->addCallback(l2->getButtonState(5), BUTTON_STATE::BTN_ACTIVE, 1, &RoadMap::openLevel, this);
		cb_handler->addCallback(l2->getButtonState(6), BUTTON_STATE::BTN_ACTIVE, 2, &RoadMap::openLevel, this);
		cb_handler->addCallback(l2->getButtonState(7), BUTTON_STATE::BTN_ACTIVE, 3, &RoadMap::openLevel, this);
		l2->setAlignment("center 20", "center 0");

		l0->createElementLine();
		tmp = l0->calculatePFNII(100, 30, 0);
		Group* l3 = new Group(tmp->third, tmp->fourth, Vector2f(tmp->first, tmp->second));
		delete tmp;

		l0->addIElement((InterfaceItem*)l3, 2);
		l3->createElementLine();
		l3->addButton(300, 100, 40, font, "CLOSE", menuColor, Color::White, Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 8, 0);
		cb_handler->addCallback(l3->getButtonState(8), BUTTON_STATE::BTN_ACTIVE, 0, &PopUpWindow::setPUWStateC, level_selection);
		l3->setAlignment("center 0", "bottom 0");

		l0->setAlignment("center 0", "space around 0");
		level_selection->addGroup(l0, 0);
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
		all_static_items->update(Vector2f(Mouse::getPosition(*window)), FloatRect(window->getView().getCenter(), Vector2f(screen_width, screen_height)));
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

	void RoadMap::render(){
		window->clear();
		window->draw(background);

		all_static_items->render(window);
		if (level_selection->getState() == POP_UP_WINDOW_STATE::PUW_OPENED) {
			level_selection->update(FloatRect(window->getView().getCenter(), Vector2f(screen_width, screen_height)));
			level_selection->render();
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