#pragma once
#include "MainMenuOption.h"

using namespace sf;

class Setting : public MainMenuOption {
public:
	void enter(RenderWindow* window) override;
};

