#include "stdafx.h"
#include "RoadMap.h"

	RoadMap::RoadMap(RenderWindow* window_, double screen_w, double screen_h, Color menuColor_): window(window_), screen_height(screen_h), screen_width(screen_w), menuColor(menuColor_){
		state = MENU_STATE::CLOSED;
		initFont();
		initBackground();
		initButtons();
		setButtonsPosition();
		menu_timer.restart();
	}

	void RoadMap::initButtons() {
		space_between_buttons = 52;
		buttons_size = 82;
		buttons["1"] = new Button(330, 330, 100, 100, buttons_size, font, "1", menuColor);
		buttons["2"] = new Button(0, 0, 100, 100, buttons_size, font, "2", menuColor);
		buttons["3"] = new Button(0, 0, 100, 100, buttons_size, font, "3", menuColor);
		buttons["4"] = new Button(0, 0, 100, 100, buttons_size, font, "L", menuColor);
	}

	void RoadMap::setButtonsPosition(){
		auto i = buttons.begin();
		short first_button_x = (screen_width - (i->second->getWidth() * buttons.size() + space_between_buttons * (buttons.size() - 1))) / 2;
		for (short j = 0; i != buttons.end(); i++, j++) {
			auto tmp = i;
			if (++tmp == buttons.end())
				j += 1;
			i->second->setPosition(Vector2f((first_button_x + j * (i->second->getWidth() + space_between_buttons)), (screen_height / 2 - i->second->getHeight() / 2)));
		}
	}

	void RoadMap::initFont(){
		font = new Font();
		if (!font->loadFromFile("Fonts/Pixel.ttf")) {
			std::cout << "Error -> RoadMap -> couldn't load text font" << std::endl;
		}
	}

	void RoadMap::initBackground(){
		background.setSize(Vector2f(screen_width, screen_height));
		background.setFillColor(sf::Color(45, 49, 81, 255));
	}

	void RoadMap::updateMenuState(){
		if (menu_timer.getElapsedTime().asSeconds() >= 0.2f) {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				state = MENU_STATE::CLOSED;
			}
			menu_timer.restart();
		}
	}

	void RoadMap::updateEvents(){
		Event event;
		while (window->pollEvent(event)) {

		}
	}

	void RoadMap::update(){
		for (auto& i : buttons) {
			i.second->update(sf::Vector2f(Mouse::getPosition(*window)), sf::FloatRect(0,0,0,0));
		}

		if (buttons["1"]->isPressed()) {
			Level* level = new Level(window, screen_width, screen_height, 1, menuColor);
			level->start();
			delete level;
			menu_timer.restart();
		}
		if (buttons["2"]->isPressed()) {
			Level* level = new Level(window, screen_width, screen_height, 2, menuColor);
			level->start();
			delete level;
			menu_timer.restart();
		}
		if (buttons["3"]->isPressed()) {
			Level* level = new Level(window, screen_width, screen_height, 3, menuColor);
			level->start();
			delete level;
			menu_timer.restart();
		}
		if (buttons["4"]->isPressed()) {
			Level* level = new Level(window, screen_width, screen_height, 4, menuColor);
			level->start();
			delete level;
			menu_timer.restart();
		}
		window->setView(View(FloatRect(0, 0, screen_width, screen_height)));
		updateEvents();
	}

	void RoadMap::render(){
		window->clear();
		window->draw(background);
		for (auto& i : buttons) {
			i.second->render(window);
		}
		window->display();
	}

	void RoadMap::enter(RenderWindow* window_){
		state = MENU_STATE::OPEN;
		while (state == MENU_STATE::OPEN) {
			updateMenuState();
			update();
			render();
		}
	}