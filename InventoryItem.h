#pragma once
#include "BasicImage.h"
#include "ResourceInfo.h"
#include "InterfaceItem.h"
#include "INTERFACE_ITEM_TYPE.h"
#include "TextureManager.h"
#include "Warehouse.h"
#include "FormItem.h"

using namespace::sf;

class InventoryItem : public InterfaceItem{
protected:
	RectangleShape background;
	RectangleShape shape;
	BasicImage* image;
	ResourceInfo* r_info;
	Text text;

	int text_size;
	float width;
	float height;
	Vector2f position;
public:
	InventoryItem(float x, float y, float width_, float height_, int text_size_);
	~InventoryItem();

	void addItemInfo(TextureManager* t_manager, Warehouse* w_object, string name);
	void addItemInfo(TextureManager* t_manager, WarehouseItem* w_item);
	void clearInfo();
	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;

	void setPosition(Vector2f new_position);
	void setPositionX(float x) override;
	void setPositionY(float y) override;
	void setBColor(Color color);

	void changePosition(float offset_x, float offset_y) override;

	void update() override;
	void render() override;
};

