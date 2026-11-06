#pragma once
#include "common/Global.hpp"
#include "screens/enums/PAGE_STATE.h"
#include "ui/enums/POP_UP_WINDOW_STATE.h"
#include "ui/enums/BUTTON_STATE.h"
#include "screens/MainMenuOption.h"
#include "ui/PopUpWindow.h"
#include "game/Level.h"
#include "ui/Button.h"
#include "ui/ResourceInfo.h"
#include "game/Warehouse.h"
#include "ui/TabContainer.h"
#include "ui/ProductCard.h"
#include "ui/InventoryItem.h"

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

	Sprite background{ Global::dummyTexture };

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
	void closeRoadMap(float q);

	void render();

	void enter(RenderWindow* window_) override;
};

