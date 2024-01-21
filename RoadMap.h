#pragma once
#include "PAGE_STATE.h"
#include "POP_UP_WINDOW_STATE.h"
#include "BUTTON_STATE.h"
#include "MainMenuOption.h"
#include "PopUpWindow.h"
#include "Level.h"
#include "Button.h"

using namespace sf;

class RoadMap : public MainMenuOption{
private:
	RenderWindow* window;
	double screen_width;
	double screen_height;
	short* u;
	Group* all_static_items;
	PopUpWindow* level_selection;
	CallbacksHandler* cb_handler;

	unordered_map<string, Button*> buttons;
	short buttons_size;
	short space_between_buttons;

	TextureManager* t_manager;
	Sprite background;

	Font* font;
	Color menuColor;
	Clock menu_timer;
	short state;

	void initFont();
	void initBackground();
public:
	RoadMap(RenderWindow* window_, double screen_w, double screen_h, Color menuColor_, TextureManager* t_manager_);

	void updateMenuState();
	void updateEvents();
	void update();
	void openLevel(float level_index);

	void render();

	void enter(RenderWindow* window_) override;
};

