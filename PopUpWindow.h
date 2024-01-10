#pragma once
#include "Button.h"

using namespace sf;

class PopUpWindow{
private:
	RenderWindow* window;
	Texture background_T;
	Sprite background_S;
	int width;
	int height;

	Font *font;
	Texture label_T;
	Sprite label_S;
	Text label;
	short state;
	void *textInput;
	vector<VertexArray*> lns;
	vector<Button*> btns;

	void initLSprite();
	void initLTexture();
	void initBSprite();
	void initBTexture();
public:
	PopUpWindow(double screen_width, double screen_height, int width_, int height_, int text_size, Font* font_, string label, RenderWindow* window_);
	~PopUpWindow();
	void setBackground();
	void setSize();
	void addWButton();
	void addNWButton();
	void addDelimiter();
	void verifyBtnsPressed();

	void update(FloatRect view_cords);
	void render();
};

