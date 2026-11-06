#pragma once
#include "ui/InterfaceItem.h"

using namespace::sf;

class FormItem{
protected:
	short fi_state;
public:
	short getFIState();
	void setFIState(short state);
};

