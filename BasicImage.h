#pragma once
#include "TextureManager.h"

using namespace::sf;

class BasicImage{
protected:
	Sprite image;
	short scale;
	Vector2f position;
public:
	BasicImage();
	BasicImage(TextureManager* t_manager, int index, string name, IntRect frame);

	FloatRect getLocalBounds();
	FloatRect getGlobalBounds();

	void setPosition(float x, float y);
	void setScale(float scale_);

	virtual void update(Vector2f mouse_pos, FloatRect view_cords);
	void render(RenderTarget* target);
};

