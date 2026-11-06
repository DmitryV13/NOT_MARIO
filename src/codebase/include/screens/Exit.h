#pragma once
#include "MainMenuOption.h"

using namespace sf;

class Exit : public MainMenuOption{
public:
	void enter(RenderWindow* window) override;
};

