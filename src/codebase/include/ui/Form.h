#pragma once
#include "Group.h"
#include "FormItem.h"
#include "FORM_ITEM_STATE.h"
#include "CheckboxItem.h"

using namespace::sf;

class Form : public Group{
private:
public:
	Form(float x, float y, float width_, float height_);
	void activateForm(float q);
	InterfaceItem* getElement(int i, int j);
};

