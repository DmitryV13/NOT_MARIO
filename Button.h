#pragma once
#include "MenuItem.h"

enum BUTTON_STATE{BTN_IDLE = 0, BTN_HOVERED, BTN_ACTIVE};

class Button : public MenuItem{
private:
	short button_state;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	//sf::Color idle_color;
	sf::Color hover_color;
	//sf::Color active_color;

public:
	Button(float x, float y, float width, float height, short text_size, sf::Font* font_, string text_, Color menuColor);
	Button(float x, float y, short text_size, sf::Font* font_, string text_, Color menuColor);
	~Button();

	float getHeight();
	float getWidth();

	void setPosition(Vector2f new_pos);
	
	const bool isPressed() const;

	void update(const sf::Vector2f mouse_pos, FloatRect view_cords);
	void render(sf::RenderTarget* target) override;

};

