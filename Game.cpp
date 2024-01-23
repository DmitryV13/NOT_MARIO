#include "stdafx.h"
#include "Game.h"

	Game::Game(double screen_w, double screen_h)
		: screen_width(screen_w)
		, screen_height(screen_h)
		, options_number(3)
		, option_selected(MENU_OPTION::MENU_PLAY) {
		t_manager = new TextureManager();
		view.reset(FloatRect(0, 0, screen_width, screen_height));
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
		screen_width = desktop.width;
		screen_height = desktop.height;
		view.reset(FloatRect(0, 0, screen_width, screen_height));
		initMenuTexture();
		initMenuSprite();
		initWindow();
		initOptions();
		initBackgroundTexture();
		initBackgroundSprite();
	}

	void Game::initWindow(){
		window.create(VideoMode(screen_width, screen_height), "NOT_MARIO", Style::Fullscreen);
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
		menu_S.setScale(4.0f,4.0f);
	}

	void Game::initBackgroundTexture(){
		if (!background_T.loadFromFile("Textures/GUI/background" + std::to_string(menuGUIS)+ ".png")) {
			std::cout << "Error -> Menu -> couldn't load background texture" << std::endl;
		}
	}

	void Game::initBackgroundSprite(){\
		background_S.setTexture(background_T);
	auto r = window.getSize().y;
		background_S.setScale(static_cast<float>(window.getSize().y) / background_S.getLocalBounds().height, static_cast<float>(window.getSize().y) / background_S.getLocalBounds().height);
		background_S.setPosition((static_cast<float>(window.getSize().x) - background_S.getGlobalBounds().width) / 2, 0);
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

		options_cords[0] = IntRect(0, menuGUIS*71+0, 70, 20);
		options_cords[1] = IntRect(0, menuGUIS * 71 + 20, 112, 20);
		options_cords[2] = IntRect(0, menuGUIS * 71 + 40, 56, 20);

		selected_cords = IntRect(0, menuGUIS * 71 + 60, 11, 11);

		options_position[0] = Vector2f((screen_width / 2) - (options_cords[0].width / 2 * menu_S.getScale().x), 300);
		options_position[1] = Vector2f((screen_width / 2) - (options_cords[1].width / 2 * menu_S.getScale().x), options_position[0].y + 30 * menu_S.getScale().y);
		options_position[2] = Vector2f((screen_width / 2) - (options_cords[2].width / 2 * menu_S.getScale().x), options_position[1].y + 30 * menu_S.getScale().y);

		selected_position = Vector2f(options_position[0].x+options_cords[0].width*menu_S.getScale().x + 15* menu_S.getScale().x, options_position[0].y + (options_cords[0].height- selected_cords.height) * menu_S.getScale().x/2);
	}

	void Game::update(){
		window.setView(view);
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape) {
					window.close();
				}
				if (event.key.code == Keyboard::Up) {
					//true -> up
					moveSelected(true);
				}
				else if (event.key.code == Keyboard::Down) {
					//false -> down
					moveSelected(false);
				}
				if (event.key.code == Keyboard::Enter) {
					options[option_selected]->enter(&window);
				}
			}
			else if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					Vector2f cursor_position(Mouse::getPosition(window));
					if (isOptionHovered(cursor_position, option_selected)) {
						options[option_selected]->enter(&window);
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
		selected_position = Vector2f(options_position[option_selected].x + options_cords[option_selected].width * menu_S.getScale().x + 15 * menu_S.getScale().x, options_position[option_selected].y + (options_cords[option_selected].height - selected_cords.height) * menu_S.getScale().x / 2);
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
			&& cursor_pos.x <= options_position[option_index].x + options_cords[option_index].width * menu_S.getScale().x
			&& cursor_pos.y >= options_position[option_index].y
			&& cursor_pos.y <= options_position[option_index].y + options_cords[option_index].height * menu_S.getScale().y) {
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
