#pragma once

using namespace sf;

class InterfaceItem{
private:
public:
	virtual void render(sf::RenderTarget* target);
	virtual void update(Vector2f mouse_pos, FloatRect view_cords);
	virtual FloatRect getLocalBounds();
};

