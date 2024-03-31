#pragma once
#include "InventoryItem.h"
#include "FormItem.h"
#include "FORM_ITEM_STATE.h"
#include "FORM_ITEM_TYPE.h"
#include "INTERFACE_ITEM_TYPE.h"

using namespace::sf;

class CheckboxItem: public InventoryItem, public FormItem{
private:
	bool chosen;
	bool unpressed;
public:
	CheckboxItem(float x, float y, float width_, float height_, int text_size_);

	void setVisibility(bool visibility);

	void update() override;
	void render() override;
};

