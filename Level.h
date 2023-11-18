#pragma once

#include "Option.h"
#include "Game.h"

class Level : public Option{
private:
	double screen_width;
	double screen_height;

public:
	Level(double screen_w, double screen_h);
	void enter(sf::RenderWindow& window_) override;
};

