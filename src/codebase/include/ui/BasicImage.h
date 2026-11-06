#pragma once
#include "common/Global.hpp"
#include "common/TextureManager.h"
#include "game/Warehouse.h"

using namespace::sf;

class BasicImage{
protected:
	RectangleShape shape;
	Sprite image{ Global::dummyTexture };
	short scale;
	Vector2f position;
public:
	BasicImage();
	BasicImage(float x, float y);
	BasicImage(TextureManager* t_manager, Warehouse* w_object, string name);
	BasicImage(TextureManager* t_manager, int index, string name, IntRect frame);

	void addInfo(TextureManager* t_manager, Warehouse* w_object, string name);
	void addInfo(TextureManager* t_manager, WarehouseItem* w_item);

	FloatRect getLocalBounds();
	FloatRect getGlobalBounds();

	void setPosition(float x, float y);
	void setScale(float scale_);
	void setBColor(Color color);

	virtual void update(Vector2f mouse_pos, FloatRect view_cords);
	void render(RenderTarget* target);
};

