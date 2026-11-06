#pragma once
#include "common/Global.hpp"
#include "common/TextureManager.h"
using namespace::sf;

class ComposedIMG{
private:
	Sprite filler{ Global::dummyTexture };			 // 6*6px
	Sprite cornerTopLeft{ Global::dummyTexture };	 // 6*6px
	Sprite cornerTopRight{ Global::dummyTexture };	 // 6*6px
	Sprite cornerBottomLeft{ Global::dummyTexture }; // 6*6px
	Sprite cornerBottomRight{ Global::dummyTexture };// 6*6px

	int origin_size;
	int width;
	int height;
	float scale;

	int offsetX;
	int offsetY;
public:
	ComposedIMG(int width_, int height_, int original_size, TextureManager* manager, int index);
	ComposedIMG(int width_, int height_, int original_size, TextureManager* manager
		, int index_0, string name_0, int index_1, string name_1, int index_2, string name_2
		, int index_3, string name_3, int index_4, string name_4);

	void setPosition(int x, int y);
	void setPosition(string positionX, string positionY, int screen_width, int screen_height);
	void setPosition(string positionX, int y, int screen_width, int screen_height);
	void setPosition(int x, string positionY, int screen_width, int screen_height);
	void setScale(float scale_);

	FloatRect getLocalBounds();
	FloatRect getGlobalBounds();

	void update(FloatRect view_cords);
	void render(RenderTarget* target);
};

