#pragma once
#include "RoadMap.h"
#include "Setting.h"
#include "Exit.h"

using namespace sf;

enum MENU_OPTION{MENU_PLAY=0, MENU_SETTINGS, MENU_EXIT};

class Game{
private:
	double screen_width;
	double screen_height;

	TextureManager* t_manager;
	short menuGUIS;


	Event event;
	RenderWindow window;
	unordered_map<short, Color> menuMainColor;
	Texture menu_T;
	Texture background_T;
	Sprite menu_S;
	Sprite background_S;

	IntRect selected_cords;
	Vector2f selected_position;

	short option_selected;
	IntRect options_cords[3];
	Vector2f options_position[3];
	short options_number;
	short* options_indexes;

	MainMenuOption** options;

	void initWindow();
	void initMenuTexture();
	void initMenuSprite();
	void initBackgroundTexture();
	void initBackgroundSprite();
	void initOptions();

public:
	Game(double screen_w, double screen_h);
	Game();

	void update();
	void updateCursor();
	void updateSelected();

	void render();
	void renderBackground();
	void renderOptions();
	void renderSelected();
	void renderCursor();

	void moveSelected(bool up);
	bool isOptionHovered(Vector2f cursor_pos, short option_index);

	void start();
};

