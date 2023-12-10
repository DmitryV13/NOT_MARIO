#pragma once

using namespace sf;

class MenuItem{
private:
public:
	virtual void render(sf::RenderTarget* target);
	virtual void update(const sf::Vector2f mouse_pos);
};

