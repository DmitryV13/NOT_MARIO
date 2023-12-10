#include "stdafx.h"
#include "GameMenu.h"


	GameMenu::GameMenu(sf::RenderWindow* window_, float map_w, float map_h, short* game_state_, Color menuColor)
		:game_state(game_state_){
		this->window = window_;
		initBackground(map_w, map_h);
		initFont();
		initButtons(menuColor);
	}

	GameMenu::~GameMenu(){
		for (auto i : buttons) {
			delete i.second;
		}
	}
	
	void GameMenu::initFont(){
		font = new Font();
		if (!font->loadFromFile("Fonts/Pixel.ttf")) {
			std::cout << "Error -> GameMenu -> couldn't load text font" << std::endl;
		}
	}

	void GameMenu::initBackground(float map_w, float map_h){
		background.setSize(Vector2f(map_w, map_h));
		background.setFillColor(sf::Color(59, 66, 73, 87));
	}

	void GameMenu::initActiveItems(){

	}
	
	void GameMenu::initPassiveItems(){

	}
	
	void GameMenu::initButtons(Color menuColor){
		space_between_buttons = 32;
		buttons_size = 32;
		buttons["CONTINUE"] = new Button(300, 300, buttons_size, font, "CONTINUE", menuColor);
		buttons["RETURN TO ROAD MAP"] = new Button(300, 600, buttons_size, font, "RETURN TO ROAD MAP", menuColor);
	}
	
	void GameMenu::initNecessaryInfo(){

	}
	
	void GameMenu::initHiddenInventory(){

	}
	
	void GameMenu::initDisplayedInventory(){

	}

	void GameMenu::update(FloatRect view_cords) {
		auto i = buttons.begin();
		short first_button_y = (view_cords.height - (i->second->getHeight() * buttons.size() + space_between_buttons * (buttons.size() - 1))) / 2;
		for ( short j=0; i != buttons.end(); i++,j++) {
			i->second->setPosition(Vector2f((view_cords.width / 2 - i->second->getWidth() / 2) + view_cords.left-view_cords.width/2, (first_button_y + j * (i->second->getHeight() + space_between_buttons)) + view_cords.top - view_cords.height / 2));
		}

		for (auto &i : buttons) {
			i.second->update(sf::Vector2f(Mouse::getPosition(*window)), view_cords);
		}

		if (buttons["RETURN TO ROAD MAP"]->isPressed()) {
			*game_state = GAME_STATE::FINISHED;
		}
		if (buttons["CONTINUE"]->isPressed()) {
			*game_state = GAME_STATE::CONTINUES;
		}
	}

	void GameMenu::render() {
		window->draw(background);
		for(auto &i : buttons){
			i.second->render(window);
		}
	}

