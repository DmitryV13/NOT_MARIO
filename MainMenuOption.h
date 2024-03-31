#pragma once
#include "PAGE_STATE.h"

using namespace sf;

class MainMenuOption{
protected:
	short state;
public:
	virtual void enter(RenderWindow* window);
	void close(float param1, float param2);
};

