#pragma once

//#include "Option.h"
#include "Level.h"
#include "Setting.h"
#include "Exit.h"

enum MENU_OPTION{MENU_PLAY=0, MENU_SETTINGS, MENU_EXIT};

class Menu{
private:
	double screen_width;
	double screen_height;

	sf::Event event;
	sf::View view;
	sf::RenderWindow window;
	sf::Texture menu_T;
	sf::Texture background_T;
	sf::Sprite menu_S;
	sf::Sprite background_S;

	sf::IntRect selected_cords;
	sf::Vector2f selected_position;

	short option_selected;
	sf::IntRect options_cords[3];
	sf::Vector2f options_position[3];
	short options_number;
	short* options_indexes;

	Option** options;

public:
	Menu(double screen_w, double screen_h, short options_n);
	Menu(short options_n);

	void initWindow();
	void initMenuTexture();
	void initMenuSprite();
	void initBackgroundTexture();
	void initBackgroundSprite();
	void initOptions();

	void update();
	void updateCursor();
	void updateSelected();

	void render();
	void renderBackground();
	void renderOptions();
	void renderSelected();
	void renderCursor();

	void moveSelected(bool up);
	bool isOptionHovered(sf::Vector2f cursor_pos, short option_index);

	void start();
};

