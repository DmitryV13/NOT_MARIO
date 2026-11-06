#include "stdafx.h"
#include "game/Game.h"

	Game::Game(double screen_w, double screen_h)
		: screen_width(screen_w)
		, screen_height(screen_h)
		, options_number(3)
		, option_selected(MENU_OPTION::MENU_PLAY) {
		t_manager = new TextureManager();
		view = sf::View(sf::FloatRect(
			{ 0.f, 0.f },
			{ static_cast<float>(screen_width), static_cast<float>(screen_height) }
		));
		initMenuTexture();
		initMenuSprite();
		initWindow();
		initOptions();
	}

	Game::Game()
		: options_number(3)
		, option_selected(MENU_OPTION::MENU_PLAY) {
		t_manager = new TextureManager();
		VideoMode desktop = VideoMode::getDesktopMode();
		screen_width = desktop.size.x;
		screen_height = desktop.size.y;
		view = sf::View(sf::FloatRect(
			{ 0.f, 0.f },
			{ static_cast<float>(screen_width), static_cast<float>(screen_height) }
		));
		initMenuTexture();
		initMenuSprite();
		initWindow();
		initOptions();
		initBackgroundTexture();
		initBackgroundSprite();
		//////////////////////////////////

		

		//////////////////////////////////
	}

	void Game::initWindow(){
		window.create(
			sf::VideoMode({static_cast<unsigned int>(screen_width), static_cast<unsigned int>(screen_height)}),
			"NOT_MARIO",
			sf::Style::Default
		);
		window.setFramerateLimit(144);
		window.setView(view);
		window.setFramerateLimit(144);
		//window.setMouseCursorVisible(false);
		//cursor = new Cursor();
	}

	void Game::initMenuTexture(){
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> menuDist(0, 2);
		menuGUIS = menuDist(gen);

		menuMainColor[0] = Color(231, 71, 57, 255);
		menuMainColor[1] = Color(170, 57, 231, 255);
		menuMainColor[2] = Color(146, 168, 56, 255);

		if (!menu_T.loadFromFile("Textures/GUI/menu1.png")) {
			std::cout << "Error -> Menu -> couldn't load menu texture" << std::endl;
		}
	}

	void Game::initMenuSprite() {
		menu_S.setTexture(menu_T);
		menu_S.setScale(sf::Vector2f(4.0f, 4.0f));
	}

	void Game::initBackgroundTexture(){
		if (!background_T.loadFromFile("Textures/GUI/background" + std::to_string(menuGUIS)+ ".png")) {
			std::cout << "Error -> Menu -> couldn't load background texture" << std::endl;
		}
	}

	void Game::initBackgroundSprite(){\
		background_S.setTexture(background_T);
	auto r = window.getSize().y;
		background_S.setScale(sf::Vector2f(static_cast<float>(window.getSize().y) / background_S.getLocalBounds().size.y, static_cast<float>(window.getSize().y) / background_S.getLocalBounds().size.y));
		background_S.setPosition(sf::Vector2f((static_cast<float>(window.getSize().x) - background_S.getGlobalBounds().size.x) / 2, 0));
	}


	void Game::initOptions(){
		options = new MainMenuOption*[options_number];
		options[0] = new RoadMap(&window, screen_width, screen_height, menuMainColor[menuGUIS], t_manager);
		options[1] = new Setting();
		options[2] = new Exit();

		options_indexes = new short[options_number];
		for (int i = 0; i < options_number; i++) {
			options_indexes[i] = i;
		}

		options_cords[0] = IntRect(sf::Vector2i(0, menuGUIS*71+0), sf::Vector2i(70, 20));
		options_cords[1] = IntRect(sf::Vector2i(0, menuGUIS * 71 + 20), sf::Vector2i(112, 20));
		options_cords[2] = IntRect(sf::Vector2i(0, menuGUIS * 71 + 40), sf::Vector2i(56, 20));

		selected_cords = IntRect(sf::Vector2i(0, menuGUIS * 71 + 60), sf::Vector2i(11, 11));

		options_position[0] = Vector2f((screen_width / 2) - (options_cords[0].size.x / 2 * menu_S.getScale().x), 300);
		options_position[1] = Vector2f((screen_width / 2) - (options_cords[1].size.x / 2 * menu_S.getScale().x), options_position[0].y + 30 * menu_S.getScale().y);
		options_position[2] = Vector2f((screen_width / 2) - (options_cords[2].size.x / 2 * menu_S.getScale().x), options_position[1].y + 30 * menu_S.getScale().y);

		selected_position = Vector2f(options_position[0].x+options_cords[0].size.x *menu_S.getScale().x + 15* menu_S.getScale().x, options_position[0].y + (options_cords[0].size.y- selected_cords.size.y) * menu_S.getScale().x/2);
	}

	void Game::update(){
		window.setView(view);
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
				if (key->code == sf::Keyboard::Key::Escape) {
					window.close();
				}
				if (key->code == sf::Keyboard::Key::Up) {
					//true -> up
					moveSelected(true);
				}
				else if (key->code == sf::Keyboard::Key::Down) {
					//false -> down
					moveSelected(false);
				}
				if (key->code == sf::Keyboard::Key::Enter) {
					options[option_selected]->enter(&window);
				}
			}
			else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouse->button == sf::Mouse::Button::Left) {
					Vector2f cursor_position(Mouse::getPosition(window));
					if (isOptionHovered(cursor_position, option_selected)) {
						options[option_selected]->enter(&window);
					}
				}
				//if (event.mouseButton.button == sf::Mouse::Button::Left) {
				//
				//}
			}
			//event.type == sf::Event::KeyReleased) {
			//if (event.key.code == sf::Keyboard::Key::D) {
			//	player->resetAnimationTimer();
			//}
		}
		updateCursor();
		updateSelected();
		
		//std::cout << sizeof(*this) << std::endl;

	}

	void Game::updateCursor(){
		Vector2f cursor_position(Mouse::getPosition(window));
		//std::cout << cursor_position.x << "  " << cursor_position.y << std::endl;
		for (int i = 0; i < options_number; i++){
			if (isOptionHovered(cursor_position, i)) {
				option_selected = i;
			}
		}
	}

	void Game::updateSelected(){
		selected_position = Vector2f(options_position[option_selected].x + options_cords[option_selected].size.x * menu_S.getScale().x + 15 * menu_S.getScale().x, options_position[option_selected].y + (options_cords[option_selected].size.y - selected_cords.size.y) * menu_S.getScale().x / 2);
	}

	void Game::render(){
		window.clear(Color::Black);
		renderBackground();
		renderOptions();
		renderSelected();
		window.display();
	}

	void Game::renderBackground(){
		window.draw(background_S);
	}

	void Game::renderOptions(){
		for (int i = 0; i < options_number; i++) {
			menu_S.setTextureRect(options_cords[i]);
			menu_S.setPosition(options_position[i]);
			window.draw(menu_S);
		}
	}

	void Game::renderSelected(){
		menu_S.setTextureRect(selected_cords);
		menu_S.setPosition(selected_position);
		window.draw(menu_S);
	}

	void Game::renderCursor(){
	}

	void Game::moveSelected(bool up){
		if (up) 
			option_selected = option_selected - 1 < 0 ? options_number - 1 : option_selected - 1;
		else
			option_selected = option_selected + 1 >= options_number ? 0 : option_selected + 1;
	}

	bool Game::isOptionHovered(Vector2f cursor_pos, short option_index){
		if (cursor_pos.x >= options_position[option_index].x
			&& cursor_pos.x <= options_position[option_index].x + options_cords[option_index].size.x * menu_S.getScale().x
			&& cursor_pos.y >= options_position[option_index].y
			&& cursor_pos.y <= options_position[option_index].y + options_cords[option_index].size.y * menu_S.getScale().y) {
			return true;
		}
		return false;
	}

	void Game::start(){
		while (window.isOpen()) {
			update();
			render();
		}
	}
