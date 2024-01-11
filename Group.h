#pragma once
#include "InterfaceItem.h"

using namespace::sf;

class Group : InterfaceItem{
private:
	Text name;
	vector<InterfaceItem*> g_elements;

	int width;
	int height;
public:

};

