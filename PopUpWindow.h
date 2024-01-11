#pragma once
#include "Button.h"
#include "ComposedIMG.h"
#include "Label.h"

using namespace sf;

class PopUpWindow{
private:
	TextureManager* manager;
	RenderWindow* window;
	ComposedIMG* w_background;
	RectangleShape* background;
	Label* label;
	int width;
	int height;

	short state;
	void *textInput;
	vector<VertexArray*> lns;
	vector<Button*> btns;

public:
	PopUpWindow(double screen_width, double screen_height, int width_, int height_, RenderWindow* window_);
	~PopUpWindow();
	void setBackground();
	void setSize();
	void addLabel(double screen_width, double screen_height, const string& label_text, Font* font_, int text_size, short offset);
	void addBackground(double map_width, double map_height, Color color);
	void addWButton();
	void addNWButton();
	void addDelimiter();
	void verifyBtnsPressed();

	void update(FloatRect view_cords);
	void render();
};

