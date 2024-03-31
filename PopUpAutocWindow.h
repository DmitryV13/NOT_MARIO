#pragma once
#include "PopUpWindow.h"

class PopUpAutocWindow: public PopUpWindow{
private:
	ImageButton* close_b;
	RectangleShape header;
	Textarea* window_name;
public:
	PopUpAutocWindow(double screen_width, double screen_height, int width_, int height_,
		TextureManager* t_manager_);

	void setWindowName(string name);

	void update() override;
	void render() override;
};

