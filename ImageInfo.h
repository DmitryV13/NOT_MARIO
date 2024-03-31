#pragma once
#include "TextureManager.h"
#include "Warehouse.h"
#include "InterfaceItem.h"
#include "INTERFACE_ITEM_TYPE.h"

using namespace::sf;

class ImageInfo : public InterfaceItem {
protected:
	RectangleShape shape;//*2
	Text text;
	Sprite src_img;//*2
	Vector2f position;
public:
	ImageInfo();
	ImageInfo(float x, float y, string text_, int text_size, TextureManager* t_manager, int index, string name);
	ImageInfo(float x, float y, int text_, int text_size, TextureManager* t_manager, int index, string name);

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;

	virtual void setPosition(Vector2f new_position);
	void setPositionX(float x) override;
	void setPositionY(float y) override;
	void setText(float text_);
	void setBackgroundColor(Color color);

	void changePosition(float offset_x, float offset_y) override;

	void update() override;
	void render() override;
};

