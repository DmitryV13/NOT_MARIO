#include "stdafx.h"
#include "RoadMap.h"

	RoadMap::RoadMap(RenderWindow* window_, double screen_w, double screen_h, Color menuColor_, TextureManager* t_manager_)
		: window(window_), screen_height(screen_h), screen_width(screen_w), menuColor(menuColor_), t_manager(t_manager_){
		state = PAGE_STATE::PAGE_CLOSED;

		initFont();
		initBackground();
		menu_timer.restart();

		cb_handler = new CallbacksHandler();
		warehouse = new Warehouse();
		
		all_static_items = new Group(0, 0, screen_width, screen_height);
		level_selection = new PopUpWindow(screen_width, screen_height, 800, 800, window);
		shop = new PopUpWindow(screen_width, screen_height, 1000, 800, window);
		inventory = new PopUpWindow(screen_width, screen_height, 1000, 800, window);

		///////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////

		all_static_items->createElementLine();
		CRect<float>* tmp = all_static_items->calculatePFNII(100, 15, 0);
		Group* asi_g0_top = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
		all_static_items->addIElement((InterfaceItem*)asi_g0_top, 0);
		
		asi_g0_top->createElementLine();
		tmp = asi_g0_top->calculatePFNII(20, 100, 0);
		Group* asi_g0_g0_left = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
		asi_g0_top->addIElement((InterfaceItem*)asi_g0_g0_left, 0);

		asi_g0_g0_left->createElementLine();
		asi_g0_g0_left->addButton(240, 80, 40, font, "SHOP", Color::White, Color::White,
			Color(14, 178, 12, 255), Color(14, 178, 12, 255), true, 10, 0);
		cb_handler->addCallback(asi_g0_g0_left->getButtonState(10), BUTTON_STATE::BTN_ACTIVE, 0,
			&PopUpWindow::setPUWStateO, shop);

		tmp = asi_g0_top->calculatePFNII(60, 100, 0);
		Group* asi_g0_g1_center = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
		asi_g0_top->addIElement((InterfaceItem*)asi_g0_g1_center, 0);

		asi_g0_g1_center->createElementLine();
		tmp = asi_g0_g1_center->calculatePFNII(5, 100, 0);
		ResourceInfo* asi_g0_g1_ri0_left = new ResourceInfo(tmp->first, tmp->second, warehouse->getItemInfo("currency", "Coin").first,
			warehouse->getItemInfo("currency", "Coin").second, 30, font, t_manager, 0, "Coin", false);
		asi_g0_g1_center->addIElement((InterfaceItem*)asi_g0_g1_ri0_left, 0);
		delete tmp;

		tmp = asi_g0_g1_center->calculatePFNII(5, 100, 0);
		ResourceInfo* asi_g0_g1_ri1_center = new ResourceInfo(tmp->first, tmp->second, warehouse->getItemInfo("currency", "BSplinter").first,
			warehouse->getItemInfo("currency", "BSplinter").second, 30, font, t_manager, 0, "BSplinter", false);
		asi_g0_g1_center->addIElement((InterfaceItem*)asi_g0_g1_ri1_center, 0);
		delete tmp;
		
		tmp = asi_g0_g1_center->calculatePFNII(5, 100, 0);
		ResourceInfo* asi_g0_g1_ri2_right = new ResourceInfo(tmp->first, tmp->second, warehouse->getItemInfo("currency", "RSplinter").first,
			warehouse->getItemInfo("currency", "RSplinter").second, 30, font, t_manager, 0, "RSplinter", false);
		asi_g0_g1_center->addIElement((InterfaceItem*)asi_g0_g1_ri2_right, 0);
		delete tmp;

		tmp = asi_g0_top->calculatePFNII(20, 100, 0);
		Group* asi_g0_g2_right = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
		asi_g0_top->addIElement((InterfaceItem*)asi_g0_g2_right, 0);
		
		asi_g0_g2_right->createElementLine();
		asi_g0_g2_right->addButton(80, 80, 40, font, "", menuColor, Color::White, Color(108, 82, 59, 255)
			, Color(163, 118, 76, 255), t_manager, 0, "ArrowBack", true, 9, 0);
		cb_handler->addCallback(asi_g0_g2_right->getButtonState(9), BUTTON_STATE::BTN_ACTIVE, 0, &RoadMap::closeRoadMap, this);
		
		asi_g0_g0_left->setAlignment("left 30", "center 0");
		asi_g0_g1_center->setAlignment("center 160", "center 0");
		asi_g0_g2_right->setAlignment("right 30", "center 0");
		asi_g0_top->setAlignment("space between 0", "top 0");

		all_static_items->createElementLine();
		tmp = all_static_items->calculatePFNII(100, 50, 0);
		Group* asi_g1_center = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
		all_static_items->addIElement((InterfaceItem*)asi_g1_center, 1);
		
		asi_g1_center->createElementLine();
		tmp = asi_g1_center->calculatePFNII(30, 100, 0);
		Reviewer* asi_g1_r0_center = new Reviewer(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
		asi_g1_center->addButton(100, 100, 40, font, "", menuColor, Color::White, Color(239, 135, 6, 255)
			, Color(255, 185, 12), t_manager, 0, "ArrowL", true, 0, 0);
		cb_handler->addCallback(asi_g1_center->getButtonState(0), BUTTON_STATE::BTN_ACTIVE, -1,
			&Reviewer::changeCurrentImage, asi_g1_r0_center);
		asi_g1_center->addIElement((InterfaceItem*)asi_g1_r0_center, 0);
		asi_g1_center->addButton(100, 100, 40, font, "", menuColor, Color::White, Color(239, 135, 6, 255)
			, Color(255, 185, 12), t_manager, 0, "ArrowR", true, 1, 0);
		cb_handler->addCallback(asi_g1_center->getButtonState(1), BUTTON_STATE::BTN_ACTIVE, 1,
			&Reviewer::changeCurrentImage, asi_g1_r0_center);

		asi_g1_r0_center->addAnimatedImage(t_manager, warehouse, "Hero1");
		asi_g1_r0_center->addAnimatedImage(t_manager, warehouse, "Hero2");
		asi_g1_center->setAlignment("center 0", "center 0");

		all_static_items->createElementLine();
		tmp= all_static_items->calculatePFNII(100, 20, 0);
		Group* asi_g2_bottom = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
		all_static_items->addIElement((InterfaceItem*)asi_g2_bottom, 2);

		asi_g2_bottom->createElementLine();
		asi_g2_bottom->addButton(400, 120, 40, font, "INVENTORY", Color::White, Color::White,
			Color(212, 24, 22, 255), Color(212, 24, 22, 255), true, 2, 0);
		cb_handler->addCallback(asi_g2_bottom->getButtonState(2), BUTTON_STATE::BTN_ACTIVE, 0,
			&PopUpWindow::setPUWStateO, inventory);
		asi_g2_bottom->addButton(400, 120, 40, font, "PLAY", Color::White, Color::White,
			Color(43, 95, 194, 255), Color(43, 95, 194, 255), true, 3, 0);
		cb_handler->addCallback(asi_g2_bottom->getButtonState(3), BUTTON_STATE::BTN_ACTIVE, 0,
			&PopUpWindow::setPUWStateO, level_selection);
		asi_g2_bottom->setAlignment("space between 200", "center 0");
		
		all_static_items->setAlignment("center 0", "bottom 0");
		asi_g0_top->changePositionY(-120);

		///////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////

		level_selection->addBackground(screen_width, screen_height, Color(59, 66, 73, 87));
		level_selection->createGroupLine();
		tmp = level_selection->calculatePFNG(100, 100, 0);
		Group* ls= new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;

		ls->addGroupName("Select level", 50, font);
		ls->createElementLine();
		tmp = ls->calculatePFNII(100, 30, 0);
		Group* ls_g0_top=new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;

		ls->addIElement((InterfaceItem*)ls_g0_top, 0);
		ls_g0_top->addGroupName("Static levels", 30, font);
		ls_g0_top->createElementLine();
		ls_g0_top->addButton(100, 100, 40, font, "1", menuColor, Color::White, Color(43, 43, 120, 255),
			Color(43, 43, 120, 255), false, 4, 0);
		level_selection->addCallback(ls_g0_top->getButtonState(4), BUTTON_STATE::BTN_ACTIVE, 4,
			&RoadMap::openLevel, this);
		ls_g0_top->setAlignment("center 20", "center 0");

		ls->createElementLine();
		tmp = ls->calculatePFNII(100, 30, 0);
		Group* ls_g1_center = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;

		ls->addIElement((InterfaceItem*)ls_g1_center, 1);
		ls_g1_center->addGroupName("Infinite levels", 30, font);
		ls_g1_center->createElementLine();
		ls_g1_center->addButton(100, 100, 40, font, "1", menuColor, Color::White, Color(43, 43, 120, 255),
			Color(43, 43, 120, 255), false, 5, 0);
		ls_g1_center->addButton(100, 100, 40, font, "2", menuColor, Color::White, Color(43, 43, 120, 255),
			Color(43, 43, 120, 255), false, 6, 0);
		ls_g1_center->addButton(100, 100, 40, font, "3", menuColor, Color::White, Color(43, 43, 120, 255),
			Color(43, 43, 120, 255), false, 7, 0);
		level_selection->addCallback(ls_g1_center->getButtonState(5), BUTTON_STATE::BTN_ACTIVE, 1,
			&RoadMap::openLevel, this);
		level_selection->addCallback(ls_g1_center->getButtonState(6), BUTTON_STATE::BTN_ACTIVE, 2,
			&RoadMap::openLevel, this);
		level_selection->addCallback(ls_g1_center->getButtonState(7), BUTTON_STATE::BTN_ACTIVE, 3,
			&RoadMap::openLevel, this);
		ls_g1_center->setAlignment("center 20", "center 0");

		ls->createElementLine();
		tmp = ls->calculatePFNII(100, 30, 0);
		Group* ls_g2_bottom = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;

		ls->addIElement((InterfaceItem*)ls_g2_bottom, 2);
		ls_g2_bottom->createElementLine();
		ls_g2_bottom->addButton(300, 100, 40, font, "CLOSE", menuColor, Color::White,
			Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 8, 0);
		level_selection->addCallback(ls_g2_bottom->getButtonState(8), BUTTON_STATE::BTN_ACTIVE, 0,
			&PopUpWindow::setPUWStateC, level_selection);
		ls_g2_bottom->setAlignment("center 0", "bottom 0");

		ls->setAlignment("center 0", "space around 0");
		level_selection->addGroup(ls, 0);

		///////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////

		shop->addLabel(screen_width, screen_height, "Shop", font, 60, 10);
		shop->addBackground(screen_width, screen_height, Color(59, 66, 73, 87));
		shop->createGroupLine();

		tmp = shop->calculatePFNG(100, 100, 0);
		Group* s = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
		shop->addGroup(s, 0);

		s->createElementLine();
		tmp = s->calculatePFNII(85, 100, 0);
		TabContainer* s_tc0_left = new TabContainer(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
		s->addIElement((InterfaceItem*)s_tc0_left, 0);
		
		Group* s_tc0_0 = new Group(s_tc0_left->getGlobalBounds().left, s_tc0_left->getGlobalBounds().top, 
			s_tc0_left->getGlobalBounds().width, s_tc0_left->getGlobalBounds().height);
		s_tc0_left->addTab(s_tc0_0);
		s_tc0_0->createElementLine();

		tmp = s_tc0_0->calculatePFNII(25, 45, 0);
		Group* s_tc0_0_pc0_g=new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		ProductCard* s_tc0_0_pc0 = new ProductCard(5, 1, 1, warehouse->getItemInfo("ammunition", "Arrow1").first);
		s_tc0_0_pc0->setGroup(s_tc0_0_pc0_g, Color(61, 85, 132, 255));
		s_tc0_0_pc0->setCurrency(warehouse->getItemInfo("currency", "Coin").first);
		s_tc0_0->addIElement((InterfaceItem*)s_tc0_0_pc0, 0);
		delete tmp;

		s_tc0_0_pc0_g->createElementLine();
		tmp = s_tc0_0_pc0_g->calculatePFNII(85, 55, 0);
		Group* s_tc0_0_pc0_g_g0_top = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		s_tc0_0_pc0_g->addIElement((InterfaceItem*)s_tc0_0_pc0_g_g0_top, 0);
		delete tmp;

		s_tc0_0_pc0_g_g0_top->createElementLine();
		tmp = s_tc0_0_pc0_g_g0_top->calculatePFNII(100, 100, 0);
		Reviewer* s_tc0_0_pc0_g_g0_r = new Reviewer(tmp->first, tmp->second, tmp->third, tmp->fourth);
		s_tc0_0_pc0_g_g0_r->addStaticImage(t_manager, warehouse, "Arrow1");
		s_tc0_0_pc0_g_g0_top->addIElement((InterfaceItem*)s_tc0_0_pc0_g_g0_r, 0);
		s_tc0_0_pc0_g_g0_top->setBColor(Color(173, 173, 173, 255));
		delete tmp;

		s_tc0_0_pc0_g->createElementLine();
		tmp = s_tc0_0_pc0_g->calculatePFNII(85, 10, 0);
		ResourceInfo* s_tc0_0_pc0_g_ii1_center = new ResourceInfo(tmp->first, tmp->second,
			s_tc0_0_pc0->getPrice(), 0, 24, font, t_manager, 0, "Coin", true);
		s_tc0_0_pc0_g->addIElement((InterfaceItem*)s_tc0_0_pc0_g_ii1_center, 1);
		delete tmp;

		tmp = s_tc0_0_pc0_g->calculatePFNII(85, 20, 0);
		s_tc0_0_pc0_g->createElementLine();
		s_tc0_0_pc0_g->addButton(tmp->third, tmp->fourth-1, 30, font, "BUY", Color::White,
			Color::White, Color(239, 135, 6, 255), Color(239, 135, 6, 255), false, 14, 2);
		shop->addCallback(s_tc0_0_pc0_g->getButtonState(14), BUTTON_STATE::BTN_ACTIVE, 0,
			&ProductCard::buy, s_tc0_0_pc0);
		delete tmp;

		s_tc0_0_pc0->addNotification(30, font, Color::White);
		s_tc0_0_pc0->setAlignment("center 0", "space around");
		s_tc0_0->setAlignment("left 20", "top 20");

		Group* s_tc0_1 = new Group(s_tc0_left->getGlobalBounds().left, s_tc0_left->getGlobalBounds().top, 
			s_tc0_left->getGlobalBounds().width, s_tc0_left->getGlobalBounds().height);
		s_tc0_left->addTab(s_tc0_1);
		s_tc0_1->createElementLine();

		s_tc0_1->addButton(300, 60, 20, font, "UPGRADE", menuColor, Color::White,
			Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 5, 0);

		tmp = s->calculatePFNII(15, 100, 0);
		Group* s_g1_right = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		s->addIElement((InterfaceItem*)s_g1_right, 0);

		s_g1_right->createElementLine();
		s_g1_right->addButton(tmp->third, 60, 20, font, "BUY", menuColor, Color::White,
			Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 11, 0);
		shop->addCallback(s_g1_right->getButtonState(11), BUTTON_STATE::BTN_ACTIVE, 0,
			&TabContainer::changeCurrentTab, s_tc0_left);
		s_g1_right->createElementLine();
		s_g1_right->addButton(tmp->third, 60, 20, font, "UPGRADE", menuColor, Color::White,
			Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 12, 1);
		shop->addCallback(s_g1_right->getButtonState(12), BUTTON_STATE::BTN_ACTIVE, 1,
			&TabContainer::changeCurrentTab, s_tc0_left);
		s_g1_right->createElementLine();
		s_g1_right->addButton(tmp->third, 60, 20, font, "CLOSE", menuColor, Color::White,
			Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 13, 2);
		shop->addCallback(s_g1_right->getButtonState(13), BUTTON_STATE::BTN_ACTIVE, 0,
			&PopUpWindow::setPUWStateC, shop);
		s_g1_right->setAlignment("center 0", "top 5");
		delete tmp;

		///////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////  14

		inventory->addLabel(screen_width, screen_height, "Inventory", font, 60, 10);
		inventory->addBackground(screen_width, screen_height, Color(59, 66, 73, 87));
		inventory->createGroupLine();

		tmp = inventory->calculatePFNG(100, 100, 0);
		Group* i = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
		inventory->addGroup(i, 0);

		i->createElementLine();
		tmp = i->calculatePFNII(85, 100, 0);
		TabContainer* i_tc0_left = new TabContainer(tmp->first, tmp->second, tmp->third, tmp->fourth);
		delete tmp;
		i->addIElement((InterfaceItem*)i_tc0_left, 0);

		Group* i_tc0_0 = new Group(i_tc0_left->getGlobalBounds().left, i_tc0_left->getGlobalBounds().top,
			i_tc0_left->getGlobalBounds().width, i_tc0_left->getGlobalBounds().height);
		i_tc0_left->addTab(i_tc0_0);

		for (int in = 0; in < 5; in++) {
			i_tc0_0->createElementLine();
			for (int jn = 0; jn < 6; jn++) {
				tmp = i_tc0_0->calculatePFNII(15, 18, in);
				Group* temp = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);

				delete tmp;
				i_tc0_0->addIElement((InterfaceItem*)temp, in);
				temp->setBColor(Color::Red);
			}
		}
		i_tc0_0->setAlignment("space around", "space around");

		Group* i_tc0_1 = new Group(i_tc0_left->getGlobalBounds().left, i_tc0_left->getGlobalBounds().top,
			i_tc0_left->getGlobalBounds().width, i_tc0_left->getGlobalBounds().height);
		i_tc0_left->addTab(i_tc0_1);

		for (int in = 0; in < 5; in++) {
			i_tc0_1->createElementLine();
			for (int jn = 0; jn < 6; jn++) {
				tmp = i_tc0_1->calculatePFNII(15, 18, in);
				Group* temp = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
				delete tmp;
				i_tc0_1->addIElement((InterfaceItem*)temp, in);
				temp->setBColor(Color::Cyan);
			}
		}
		i_tc0_1->setAlignment("space around", "space around");

		Group* i_tc0_2 = new Group(i_tc0_left->getGlobalBounds().left, i_tc0_left->getGlobalBounds().top,
			i_tc0_left->getGlobalBounds().width, i_tc0_left->getGlobalBounds().height);
		i_tc0_left->addTab(i_tc0_2);

		for (int in = 0; in < 5; in++) {
			i_tc0_2->createElementLine();
			for (int jn = 0; jn < 6; jn++) {
				tmp = i_tc0_2->calculatePFNII(15, 18, in);
				Group* temp = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
				delete tmp;
				i_tc0_2->addIElement((InterfaceItem*)temp, in);
				temp->setBColor(Color::Green);
			}
		}
		i_tc0_2->setAlignment("space around", "space around");

		Group* i_tc0_3 = new Group(i_tc0_left->getGlobalBounds().left, i_tc0_left->getGlobalBounds().top,
			i_tc0_left->getGlobalBounds().width, i_tc0_left->getGlobalBounds().height);
		i_tc0_left->addTab(i_tc0_3);

		for (int in = 0; in < 5; in++) {
			i_tc0_3->createElementLine();
			for (int jn = 0; jn < 6; jn++) {
				tmp = i_tc0_3->calculatePFNII(15, 18, in);
				Group* temp = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
				InventoryItem* temp_i = new InventoryItem(tmp->first, tmp->second, tmp->third, tmp->fourth,
					15, font);
				temp->createElementLine();
				temp->addIElement((InterfaceItem*)temp_i, 0);
				temp_i->addItemInfo(t_manager, warehouse, "Arrow1");
				delete tmp;
				i_tc0_3->addIElement((InterfaceItem*)temp, in);
				temp->setBColor(Color(118, 118, 118, 255));
			}
		}
		i_tc0_3->setAlignment("space around", "space around");

		tmp = i->calculatePFNII(15, 100, 0);
		Group* i_g1_right = new Group(tmp->first, tmp->second, tmp->third, tmp->fourth);
		i->addIElement((InterfaceItem*)i_g1_right, 0);

		i_g1_right->createElementLine();
		i_g1_right->addButton(tmp->third, 60, 20, font, "WEAPONS", menuColor, Color::White,
			Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 15, 0);
		inventory->addCallback(i_g1_right->getButtonState(15), BUTTON_STATE::BTN_ACTIVE, 0,
			&TabContainer::changeCurrentTab, i_tc0_left);

		i_g1_right->createElementLine();
		i_g1_right->addButton(tmp->third, 60, 20, font, "AMMO", menuColor, Color::White,
			Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 16, 1);
		inventory->addCallback(i_g1_right->getButtonState(16), BUTTON_STATE::BTN_ACTIVE, 1,
			&TabContainer::changeCurrentTab, i_tc0_left);

		i_g1_right->createElementLine();
		i_g1_right->addButton(tmp->third, 60, 20, font, "POTIONS", menuColor, Color::White,
			Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 17, 2);
		inventory->addCallback(i_g1_right->getButtonState(17), BUTTON_STATE::BTN_ACTIVE, 2,
			&TabContainer::changeCurrentTab, i_tc0_left);

		i_g1_right->createElementLine();
		i_g1_right->addButton(tmp->third, 60, 20, font, "OTHER", menuColor, Color::White,
			Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 18, 3);
		inventory->addCallback(i_g1_right->getButtonState(18), BUTTON_STATE::BTN_ACTIVE, 3,
			&TabContainer::changeCurrentTab, i_tc0_left);

		i_g1_right->createElementLine();
		i_g1_right->addButton(tmp->third, 60, 20, font, "CLOSE", menuColor, Color::White,
			Color(43, 43, 120, 255), Color(43, 43, 120, 255), false, 19, 4);
		inventory->addCallback(i_g1_right->getButtonState(19), BUTTON_STATE::BTN_ACTIVE, 0,
			&PopUpWindow::setPUWStateC, inventory);

		delete tmp;
		i_g1_right->setAlignment("center 0", "top 5");
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
			shop->getState() == POP_UP_WINDOW_STATE::PUW_CLOSED && 
			inventory->getState() == POP_UP_WINDOW_STATE::PUW_CLOSED) {
			all_static_items->update(Vector2f(Mouse::getPosition(*window)), FloatRect(window->getView().getCenter(), Vector2f(screen_width, screen_height)));
		}
		cb_handler->update();

		window->setView(View(FloatRect(0, 0, screen_width, screen_height)));
		updateEvents();
	}

	void RoadMap::openLevel(float level_index){
		Level* level;
		if(level_index<4)
			level = new Level(window, screen_width, screen_height, static_cast<int>(level_index), menuColor, t_manager, warehouse, -1);
		else
			level = new Level(window, screen_width, screen_height, static_cast<int>(level_index), menuColor, t_manager, warehouse, 1);
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
		if (inventory->getState() == POP_UP_WINDOW_STATE::PUW_OPENED) {
			inventory->update(FloatRect(window->getView().getCenter(), Vector2f(screen_width, screen_height)));
			inventory->render();
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