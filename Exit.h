#pragma once

#include "Option.h"

class Exit : public Option{
public:
	void enter(sf::RenderWindow& window) override;
};

