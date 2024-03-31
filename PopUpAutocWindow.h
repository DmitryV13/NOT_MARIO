#pragma once
#include "PopUpWindow.h"

class PopUpAutocWindow: public PopUpWindow{
private:
	ImageButton* close_b;
	RectangleShape header;
	Textarea* window_name;

	bool chosen;

	Vector2f mouse_pressed_pos;
	float offset_x;
	float offset_y;
public:
	PopUpAutocWindow(double screen_width, double screen_height, int width_, int height_,
		TextureManager* t_manager_);

	void setWindowName(string name);
	void dragWindow(Vector2f mouse_current_pos);

	void update() override;
	void render() override;
};

