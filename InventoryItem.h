#pragma once
#include "BasicImage.h"
#include "ResourceInfo.h"
#include "InterfaceItem.h"
#include "INTERFACE_ITEM_TYPE.h"
#include "TextureManager.h"
#include "Warehouse.h"

using namespace::sf;

class InventoryItem : public InterfaceItem{
private:
	BasicImage* image;
	ResourceInfo* r_info;
	Text text;

	int text_size;
	float width;
	float height;

	Vector2f position;
public:
	InventoryItem(float x, float y, float width_, float height_, int text_size_, Font* font);

	void addItemInfo(TextureManager* t_manager, Warehouse* w_object, string name);

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;

	void setPosition(Vector2f new_position);
	void setPositionX(float x) override;
	void setPositionY(float y) override;

	void changePosition(float offset_x, float offset_y) override;

	void update(Vector2f mouse_pos, FloatRect view_cords) override;
	void render(RenderTarget* target) override;
};

