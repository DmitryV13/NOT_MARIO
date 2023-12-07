#pragma once
#include "MENU_STATE.h"
#include "MainMenuOption.h"
#include "Level.h"
#include "Button.h"

using namespace sf;

class RoadMap : public MainMenuOption{
private:
	RenderWindow* window;
	double screen_width;
	double screen_height;

	unordered_map<string, Button*> buttons;
	short buttons_size;
	short space_between_buttons;

	RectangleShape background;

	Font* font;
	Clock menu_timer;
	short state;

	void initButtons();
	void setButtonsPosition();
	void initFont();
	void initBackground();
public:
	RoadMap(RenderWindow* window_, double screen_w, double screen_h);

	void updateMenuState();
	void updateEvents();
	void update();

	void render();

	void enter(RenderWindow* window_) override;
};

