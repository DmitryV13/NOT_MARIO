#pragma once
#include "FormItem.h"
#include "Group.h"
#include "FORM_ITEM_STATE.h"
#include "FORM_ITEM_TYPE.h"
#include "INTERFACE_ITEM_TYPE.h"

using namespace::sf;

class CheckboxItem: public Group, public FormItem{
private:
	RectangleShape shape;
	bool chosen;
	bool unpressed;
	string* value;
	string active_value;
	string idle_value;
public:
	CheckboxItem(float x, float y, float width_, float height_);
	~CheckboxItem();

	string* getValue();

	void setValue(string val);

	void update() override;
	void render() override;
};

