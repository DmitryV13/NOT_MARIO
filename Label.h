#pragma once
#include "ComposedIMG.h"

using namespace::sf;

class Label{
private:
	ComposedIMG* label_background;
	Text* label_text;
	int text_size;
public:
	Label(const string& label_text_, Font* font_, int text_size_, TextureManager* manager, int index);

	void setPosition(int x, int y);
	void setPosition(string positionX, string positionY, int screen_width, int screen_height);
	void setPosition(string positionX, int y, int screen_width, int screen_height);
	void setPosition(int x, string positionY, int screen_width, int screen_height);

	FloatRect getLocalBounds();
	FloatRect getGlobalBounds();

	void update(FloatRect view_cords);
	void render(RenderTarget* target);
};

