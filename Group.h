#pragma once
#include "InterfaceItem.h"

using namespace::sf;

class Group : InterfaceItem{
private:
	Text name;
	vector<InterfaceItem*> g_elements;

	short alignment;

	int width;
	int height;
public:
	Group();

	void addGroupName(string name, int name_size, Font* font);
	void addButton();
	void addDelimiter();
	void addSlider();
	void addCard();

	void update(FloatRect view_cords);
	void render(RenderTarget* target);
};

