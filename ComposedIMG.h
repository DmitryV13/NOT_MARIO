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

	int origin_size;
	int width;
	int height;
	float scale;

	Vector2f position;
public:
	ComposedIMG(int width_, int height_, int original_size, TextureManager* manager, int index);
	ComposedIMG(int width_, int height_, int original_size, TextureManager* manager
		, int index_0, string name_0, int index_1, string name_1, int index_2, string name_2
		, int index_3, string name_3, int index_4, string name_4);
	~ComposedIMG();

	void setPosition(float x, float y);
	void setPosition(string positionX, string positionY, int screen_width, int screen_height);
	void setPosition(string positionX, float y, int screen_width, int screen_height);
	void setPosition(float x, string positionY, int screen_width, int screen_height);
	void changePosition(float offset_x, float offset_y);
	void setScale(float scale_);

	FloatRect getLocalBounds();
	FloatRect getGlobalBounds();

	void update();
	void render();
};

