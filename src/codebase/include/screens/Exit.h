#pragma once
#include "screens/MainMenuOption.h"

using namespace sf;

class Exit : public MainMenuOption{
public:
	void enter(RenderWindow* window) override;
};

