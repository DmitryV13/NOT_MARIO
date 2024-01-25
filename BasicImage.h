#pragma once
#include "TextureManager.h"
#include "Warehouse.h"

using namespace::sf;

class BasicImage{
protected:
	RectangleShape shape;
	Sprite image;
	short scale;
	Vector2f position;
public:
	BasicImage();
	BasicImage(float x, float y);
	BasicImage(TextureManager* t_manager, Warehouse* w_object, string name);
	BasicImage(TextureManager* t_manager, int index, string name, IntRect frame);

	void addInfo(TextureManager* t_manager, Warehouse* w_object, string name);

	FloatRect getLocalBounds();
	FloatRect getGlobalBounds();

	void setPosition(float x, float y);
	void setScale(float scale_);
	void setBColor(Color color);

	virtual void update(Vector2f mouse_pos, FloatRect view_cords);
	void render(RenderTarget* target);
};

