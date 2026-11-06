#pragma once
#include "ui/Group.h"
#include "ui/FormItem.h"
#include "ui/enums/FORM_ITEM_STATE.h"
#include "ui/CheckboxItem.h"

using namespace::sf;

class Form : public Group{
private:
public:
	Form(float x, float y, float width_, float height_);
	void activateForm(float q);
	InterfaceItem* getElement(int i, int j);
};

