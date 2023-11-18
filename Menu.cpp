#include "stdafx.h"
#include "Menu.h"

	Menu::Menu(double screen_w, double screen_h, short options_n)
		: screen_width(screen_w)
		, screen_height(screen_h)
		, options_number(options_n)
		, option_selected(MENU_OPTION::MENU_PLAY) {
		view.reset(sf::FloatRect(0, 0, screen_width, screen_height));
		initMenuTexture();
		initMenuSprite();
		initOptions();
		initWindow();
	}

	Menu::Menu(short options_n)
		: options_number(options_n)
		, option_selected(MENU_OPTION::MENU_PLAY) {
		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
		screen_width = desktop.width;
		screen_height = desktop.height;
		view.reset(sf::FloatRect(0, 0, screen_width, screen_height));
		initMenuTexture();
		initMenuSprite();
		initOptions();
		initWindow();
		initBackgroundTexture();
		initBackgroundSprite();
	}

	void Menu::initWindow(){
		window.create(sf::VideoMode(screen_width, screen_height), "NOT_MARIO", sf::Style::Default);
		window.setFramerateLimit(144);
		window.setView(view);
		window.setFramerateLimit(144);
		//window.setMouseCursorVisible(false);
		//cursor = new Cursor();
	}

	void Menu::initMenuTexture(){
		if (!menu_T.loadFromFile("Textures/Menu/menu2.png")) {
			std::cout << "Error -> Menu -> couldn't load menu texture" << std::endl;
		}
	}

	void Menu::initMenuSprite() {
		menu_S.setTexture(menu_T);
		menu_S.setScale(4.0f,4.0f);
	}

	void Menu::initBackgroundTexture(){
		if (!background_T.loadFromFile("Textures/Menu/background.png")) {
			std::cout << "Error -> Menu -> couldn't load background texture" << std::endl;
		}
	}

	void Menu::initBackgroundSprite(){\
		background_S.setTexture(background_T);
		background_S.setScale(static_cast<float>(window.getSize().y) / background_S.getLocalBounds().height, static_cast<float>(window.getSize().y) / background_S.getLocalBounds().height);
		background_S.setPosition((static_cast<float>(window.getSize().x) - background_S.getGlobalBounds().width) / 2, 0);
	}

	void Menu::initOptions(){ 
		options = new Option*[options_number];
		options[0] = new Level(screen_width, screen_height);
		options[1] = new Setting();
		options[2] = new Exit();

		options_indexes = new short[options_number];
		for (int i = 0; i < options_number; i++) {
			options_indexes[i] = i;
		}

		options_cords[0] = sf::IntRect(0, 0, 70, 20);
		options_cords[1] = sf::IntRect(0, 20, 112, 20);
		options_cords[2] = sf::IntRect(0, 40, 56, 20);

		selected_cords = sf::IntRect(0, 60, 25, 19);

		options_position[0] = sf::Vector2f((screen_width / 2) - (options_cords[0].width / 2 * menu_S.getScale().x), 300);
		options_position[1] = sf::Vector2f((screen_width / 2) - (options_cords[1].width / 2 * menu_S.getScale().x), options_position[0].y + 30 * menu_S.getScale().y);
		options_position[2] = sf::Vector2f((screen_width / 2) - (options_cords[2].width / 2 * menu_S.getScale().x), options_position[1].y + 30 * menu_S.getScale().y);

		selected_position = sf::Vector2f(options_position[0].x+options_cords[0].width*menu_S.getScale().x + 15* menu_S.getScale().x, options_position[0].y + (options_cords[0].height- selected_cords.height) * menu_S.getScale().x/2);
	}

	void Menu::update(){
		window.setView(view);
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				if (event.key.code == sf::Keyboard::Up) {
					//true -> up
					moveSelected(true);
				}
				else if (event.key.code == sf::Keyboard::Down) {
					//false -> down
					moveSelected(false);
				}
				if (event.key.code == sf::Keyboard::Enter) {
					options[option_selected]->enter(window);
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f cursor_position(sf::Mouse::getPosition(window));
					if (isOptionHovered(cursor_position, option_selected)) {
						options[option_selected]->enter(window);
					}
				}
				//if (event.mouseButton.button == sf::Mouse::Left) {
				//
				//}
			}
			//event.type == sf::Event::KeyReleased) {
			//if (event.key.code == sf::Keyboard::D) {
			//	player->resetAnimationTimer();
			//}
		}
		updateCursor();
		updateSelected();
	}

	void Menu::updateCursor(){
		sf::Vector2f cursor_position(sf::Mouse::getPosition(window));
		//std::cout << cursor_position.x << "  " << cursor_position.y << std::endl;
		for (int i = 0; i < options_number; i++){
			if (isOptionHovered(cursor_position, i)) {
				option_selected = i;
			}
		}
	}

	void Menu::updateSelected(){
		selected_position = sf::Vector2f(options_position[option_selected].x + options_cords[option_selected].width * menu_S.getScale().x + 15 * menu_S.getScale().x, options_position[option_selected].y + (options_cords[option_selected].height - selected_cords.height) * menu_S.getScale().x / 2);
	}

	void Menu::render(){
		window.clear(sf::Color::Black);
		renderBackground();
		renderOptions();
		renderSelected();
		window.display();
	}

	void Menu::renderBackground(){
		window.draw(background_S);
	}

	void Menu::renderOptions(){
		for (int i = 0; i < options_number; i++) {
			menu_S.setTextureRect(options_cords[i]);
			menu_S.setPosition(options_position[i]);
			window.draw(menu_S);
		}
	}

	void Menu::renderSelected(){
		menu_S.setTextureRect(selected_cords);
		menu_S.setPosition(selected_position);
		window.draw(menu_S);
	}

	void Menu::renderCursor(){
	}

	void Menu::moveSelected(bool up){
		if (up) 
			option_selected = option_selected - 1 < 0 ? options_number - 1 : option_selected - 1;
		else
			option_selected = option_selected + 1 >= options_number ? 0 : option_selected + 1;
	}

	bool Menu::isOptionHovered(sf::Vector2f cursor_pos, short option_index){
		if (cursor_pos.x >= options_position[option_index].x
			&& cursor_pos.x <= options_position[option_index].x + options_cords[option_index].width * menu_S.getScale().x
			&& cursor_pos.y >= options_position[option_index].y
			&& cursor_pos.y <= options_position[option_index].y + options_cords[option_index].height * menu_S.getScale().y) {
			return true;
		}
		return false;
	}

	void Menu::start(){
		while (window.isOpen()) {
			update();
			render();
		}
	}
