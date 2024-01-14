#pragma once
#include "InterfaceItem.h"

enum BUTTON_STATE{BTN_IDLE = 0, BTN_HOVERED, BTN_ACTIVE};

class Button : public InterfaceItem{
private:
	short button_state;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	Vector2f position;
	//sf::Color idle_color;
	sf::Color hover_color;
	//sf::Color active_color;

public:
	Button(float x, float y, float width, float height, short text_size, sf::Font* font_, string text_, Color menuColor);
	Button(float x, float y, short text_size, sf::Font* font_, string text_, Color menuColor);
	~Button();

	float getHeight();
	float getWidth();
	float getTextHeight();
	float getTextWidth();
	FloatRect getLocalBounds() override;

	void setPosition(Vector2f new_position);
	void setMenuColor(Color menuColor);
	void setBackgroundColor(Color shapeColor);
	
	const bool isPressed() const;

	void updatePosition(FloatRect view_cords);
	void update(Vector2f mouse_pos, FloatRect view_cords) override;
	void render(sf::RenderTarget* target) override;

};

