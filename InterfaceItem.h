#pragma once

using namespace sf;

class InterfaceItem{
protected:
	short ii_type;
public:
	virtual FloatRect getLocalBounds();
	virtual FloatRect getGlobalBounds();
	short& getIIType();

	virtual void setPositionX(float x);
	virtual void setPositionY(float y);

	virtual void changePosition(float offset_x, float offset_y);
	virtual void resetActiveState();

	virtual void render(sf::RenderTarget* target);
	virtual void update(Vector2f mouse_pos, FloatRect view_cords);
};

