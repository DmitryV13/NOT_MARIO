#pragma once
#include "MainMenuOption.h"
#include "Level.h"

using namespace sf;

class RoadMap : public MainMenuOption{
private:
	double screen_width;
	double screen_height;

public:
	RoadMap(double screen_w, double screen_h);
	void enter(RenderWindow* window_) override;
};

