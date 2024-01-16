#pragma once
#include "InterfaceItem.h"
#include "Button.h"
#include "GAME_STATE.h"

using namespace sf;

class GameMenu{
private:
	short buttons_size;
	short space_between_buttons;

	float w_w;
	float w_h;

	short* game_state;
	sf::RenderWindow* window;

	RectangleShape background;

	Font* font;

	vector<vector<InterfaceItem*>> active_items;
	vector<vector<InterfaceItem*>> passive_items;
	unordered_map<string, Button*> buttons;
	vector<InterfaceItem*> necessary_info;
	vector<InterfaceItem*> hidden_inventory;
	vector<InterfaceItem*> displayed_inventory;

	void initFont();
	void initBackground(float map_w, float map_h);
	void initActiveItems();
	void initPassiveItems();
	void initButtons(Color menuColor);
	void initNecessaryInfo();
	void initHiddenInventory();
	void initDisplayedInventory();

public:
	GameMenu(sf::RenderWindow* window_, float map_w, float map_h, float w_w_, float w_h_, short* game_state_, Color menuColor);
	~GameMenu();

	void update(FloatRect view_cords) ;
	void render();
};

