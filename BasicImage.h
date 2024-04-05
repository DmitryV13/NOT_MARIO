#pragma once
#include "InterfaceItem.h"
#include "TextureManager.h"
#include "Warehouse.h"

using namespace::sf;

class BasicImage : public InterfaceItem{
protected:
	RectangleShape shape;
	Sprite image;
	short scale;
	Vector2f position;
public:
	BasicImage();
	BasicImage(float x, float y);
	BasicImage(TextureManager* t_manager, Warehouse* w_object, string name);
	BasicImage(float width, float height, TextureManager* t_manager, Warehouse* w_object, string name);
	BasicImage(TextureManager* t_manager, int index, string name, IntRect frame);
	BasicImage(float width, float height, TextureManager* t_manager, int index, string name, IntRect frame);
	~BasicImage();

	void addInfo(TextureManager* t_manager, Warehouse* w_object, string name);
	void addInfo(TextureManager* t_manager, WarehouseItem* w_item);

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;

	void changePosition(float offset_x, float offset_y) override;
	void setPositionX(float x) override;
	void setPositionY(float y) override;
	void setPosition(float x, float y);
	void setScale(float scale_);
	void setBColor(Color color);

	void update() override;
	void render() override;
};

