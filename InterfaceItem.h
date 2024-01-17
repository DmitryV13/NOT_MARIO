#pragma once

using namespace sf;

class InterfaceItem{
private:
public:
	virtual FloatRect getLocalBounds();

	virtual void setPositionX(float x);
	virtual void setPositionY(float y);

	virtual void changePosition(float offset_x, float offset_y);

	virtual void render(sf::RenderTarget* target);
	virtual void update(Vector2f mouse_pos, FloatRect view_cords);
};

