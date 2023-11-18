#pragma once

#include "Option.h"

class Setting : public Option {
public:
	void enter(sf::RenderWindow& window) override;
};

