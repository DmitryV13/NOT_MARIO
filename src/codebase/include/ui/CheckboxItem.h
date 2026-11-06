#pragma once
#include "ui/InventoryItem.h"
#include "ui/FormItem.h"
#include "ui/enums/FORM_ITEM_STATE.h"
#include "ui/enums/INTERFACE_ITEM_TYPE.h"

using namespace::sf;

class CheckboxItem: public InventoryItem, public FormItem{
private:
	bool chosen;
	bool unpressed;
public:
	CheckboxItem(float x, float y, float width_, float height_, int text_size_, Font* font);
	void setVisibility(bool visibility);
	void update(Vector2f mouse_pos, FloatRect view_cords) override;
	void render(RenderTarget* target) override;
};

