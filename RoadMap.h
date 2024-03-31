#pragma once
#include "PAGE_STATE.h"
#include "POP_UP_WINDOW_STATE.h"
#include "BUTTON_STATE.h"
#include "MainMenuOption.h"
#include "PopUpWindow.h"
#include "Level.h"
#include "Button.h"
#include "ResourceInfo.h"
#include "Warehouse.h"
#include "TabContainer.h"
#include "ProductCard.h"
#include "InventoryItem.h"

using namespace sf;

class RoadMap : public MainMenuOption{
private:
	RenderWindow* window;
	double screen_width;
	double screen_height;

	Warehouse* warehouse;

	Group* all_static_items;
	PopUpWindow* level_selection;
	PopUpWindow* shop;
	PopUpWindow* inventory;

	CallbacksHandler* cb_handler;

	TextureManager* t_manager;

	Sprite background;

	Font* font;
	Color menuColor;
	Clock menu_timer;

	void initFont();
	void initBackground();
public:
	RoadMap(RenderWindow* window_, double screen_w, double screen_h, Color menuColor_, TextureManager* t_manager_);

	void updateMenuState();
	void updateEvents();
	void update();
	void openLevel(float level_index, float param2);

	void render();

	void enter(RenderWindow* window_) override;
};

