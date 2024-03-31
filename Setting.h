#pragma once
#include "MainMenuOption.h"
#include "PAGE_STATE.h"
#include "PopUpAutocWindow.h"
#include "InputField.h"
#include "TextareaField.h"
#include "NumberField.h"
#include "SliderControl.h"

using namespace sf;

class Setting : public MainMenuOption {
private:
	RenderWindow* window;
	double screen_width;
	double screen_height;

	PopUpWindow* settings;
	TextureManager* t_manager;

	Sprite background;

	Font* font;
	Color menuColor;
	Clock menu_timer;

	void initFont();
public:
	Setting(RenderWindow* window_, double screen_w, double screen_h, Color menuColor_, TextureManager* t_manager_);

	void updateMenuState();
	void updateEvents();
	void update();

	void render();

	void enter(RenderWindow* window) override;
};

