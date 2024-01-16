#pragma once
#include "TextureManager.h"
using namespace::sf;

class ComposedIMG{
private:
	Sprite filler;			 // 6*6px
	Sprite cornerTopLeft;	 // 6*6px
	Sprite cornerTopRight;	 // 6*6px
	Sprite cornerBottomLeft; // 6*6px
	Sprite cornerBottomRight;// 6*6px

	int width;
	int height;

	int offsetX;
	int offsetY;
public:
	ComposedIMG(int width_, int height_, TextureManager* manager, int index);

	void setPosition(int x, int y);
	void setPosition(string positionX, string positionY, int screen_width, int screen_height);
	void setPosition(string positionX, int y, int screen_width, int screen_height);
	void setPosition(int x, string positionY, int screen_width, int screen_height);

	FloatRect getLocalBounds();
	FloatRect getGlobalBounds();

	void update(FloatRect view_cords);
	void render(RenderTarget* target);
};

