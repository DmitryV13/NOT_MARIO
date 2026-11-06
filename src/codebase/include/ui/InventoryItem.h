#pragma once
#include "common/Global.hpp"
#include "ui/BasicImage.h"
#include "ui/ResourceInfo.h"
#include "ui/InterfaceItem.h"
#include "ui/enums/INTERFACE_ITEM_TYPE.h"
#include "common/TextureManager.h"
#include "game/Warehouse.h"
#include "ui/FormItem.h"

using namespace::sf;

class InventoryItem : public InterfaceItem{
protected:
	RectangleShape background;
	RectangleShape shape;
	BasicImage* image;
	ResourceInfo* r_info;
	Font* font;
	Text text { Global::defaultFont };

	int text_size;
	float width;
	float height;
	bool visible;
	Vector2f position;
public:
	InventoryItem(float x, float y, float width_, float height_, int text_size_, Font* font_);

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

	void update(Vector2f mouse_pos, FloatRect view_cords) override;
	void render(RenderTarget* target) override;
};

