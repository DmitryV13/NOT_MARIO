#pragma once
#include "MenuItem.h"
#include "Button.h"
#include "GAME_STATE.h"

using namespace sf;

class GameMenu{
private:
	short buttons_size;
	short space_between_buttons;

	short* game_state;
	sf::RenderWindow* window;

	RectangleShape background;

	Font* font;

	vector<vector<MenuItem*>> active_items;
	vector<vector<MenuItem*>> passive_items;
	unordered_map<string, Button*> buttons;
	vector<MenuItem*> necessary_info;
	vector<MenuItem*> hidden_inventory;
	vector<MenuItem*> displayed_inventory;

	void initFont();
	void initBackground(float map_w, float map_h);
	void initActiveItems();
	void initPassiveItems();
	void initButtons();
	void initNecessaryInfo();
	void initHiddenInventory();
	void initDisplayedInventory();

public:
	GameMenu(sf::RenderWindow* window_, float map_w, float map_h, short* game_state_);

	void update(FloatRect view_cords) ;
	void render();
};

