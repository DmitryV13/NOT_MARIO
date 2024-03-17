#pragma once
#include "InterfaceItem.h"

using namespace::sf;

class FormItem{
protected:
	short fi_state;
	short fi_type;
public:
	short& getFIType();
	short& getFIState();
	void setFIState(short state);
	virtual void formEInput(Event event);
};

