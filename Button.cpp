#include "stdafx.h"
#include "Button.h"

	Button::Button(float x, float y, float width, float height, short text_size, sf::Font* font_, string text_, Color menuColor)
	:hover_color(menuColor), position(Vector2f(x, y)) {
		button_state = BUTTON_STATE::BTN_IDLE;

		shape.setPosition(position);
		shape.setSize(sf::Vector2f(width, height));

		font = font_;
		text.setFont(*font);
		text.setString(text_);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(text_size);
		text.setOutlineThickness(3.f);
		text.setOutlineColor(sf::Color(0, 0, 0, 0));
		text.setPosition(
			shape.getPosition().x +(shape.getGlobalBounds().width / 2.f) - text.getLocalBounds().width / 2.f - text.getLocalBounds().left,
			shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getLocalBounds().height / 2.f - text.getLocalBounds().top
			);
		
		//idle_color = sf::Color(100, 150, 200, 255);
		//hover_color = sf::Color(100, 100, 200, 255);
		//active_color = sf::Color(150, 100, 200, 255);

		shape.setFillColor(sf::Color(28, 26, 47, 255));
	}

	Button::Button(float x, float y, short text_size, sf::Font* font_, string text_, Color menuColor)
	:hover_color(menuColor), position(Vector2f(x, y)){
		button_state = BUTTON_STATE::BTN_IDLE;

		shape.setPosition(position);

		font = font_;
		text.setFont(*font);
		text.setString(text_);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(text_size);
		text.setOutlineThickness(3.f);
		text.setOutlineColor(sf::Color(0, 0, 0, 0));
		text.setPosition(
			shape.getPosition().x - text.getLocalBounds().left,
			shape.getPosition().y - text.getLocalBounds().top
		);

		shape.setSize(sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height));

		//idle_color = sf::Color(100, 150, 200, 255);
		//hover_color = sf::Color(100, 100, 200, 255);
		//active_color = sf::Color(150, 100, 200, 255);

		shape.setFillColor(sf::Color(0,0,0,0));
	}
	
	Button::~Button(){

	}

	float Button::getHeight(){
		return shape.getLocalBounds().height;
	}

	float Button::getWidth(){
		return shape.getLocalBounds().width;
	}

	float Button::getTextHeight(){
		return text.getLocalBounds().height;
	}

	float Button::getTextWidth(){
		return text.getLocalBounds().width;
	}

	FloatRect Button::getLocalBounds(){
		return FloatRect(position, Vector2f(shape.getLocalBounds().width, shape.getLocalBounds().height));
	}

	void Button::setPosition(Vector2f new_position){
		position = new_position;
		shape.setPosition(position);
		text.setPosition(
			shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getLocalBounds().width / 2.f - text.getLocalBounds().left,
			shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getLocalBounds().height / 2.f - text.getLocalBounds().top
		);
	}

	void Button::setMenuColor(Color menuColor){
		hover_color = menuColor;
	}

	void Button::setBackgroundColor(Color shapeColor){
		shape.setFillColor(shapeColor);
	}

	const bool Button::isPressed() const{
		if (button_state == BUTTON_STATE::BTN_ACTIVE)
			return true;
		return false;
	}

	void Button::updatePosition(FloatRect view_cords) {
		shape.setPosition(
			view_cords.left - view_cords.width / 2 + position.x,
			view_cords.top - view_cords.height / 2 + position.y);
		text.setPosition(
			shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getLocalBounds().width / 2.f - text.getLocalBounds().left,
			shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getLocalBounds().height / 2.f - text.getLocalBounds().top
		);
	}
	
	void Button::update(Vector2f mouse_pos, FloatRect view_cords){
		updatePosition(view_cords);

		button_state = BUTTON_STATE::BTN_IDLE;
		if (shape.getGlobalBounds().contains(mouse_pos.x + (view_cords.left - view_cords.width / 2), mouse_pos.y + (view_cords.top - view_cords.height / 2))) {
			button_state = BUTTON_STATE::BTN_HOVERED;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				button_state = BUTTON_STATE::BTN_ACTIVE;
			}
		}

		switch (button_state) {
			case BTN_IDLE:
				text.setOutlineColor(sf::Color(0, 0, 0, 0));
				text.setFillColor(sf::Color::White);
				//shape.setFillColor(sf::Color(50, 50, 50, 50));
				break;

			case BTN_HOVERED:
				text.setOutlineColor(sf::Color(0, 0, 0, 255));
				text.setFillColor(hover_color);
				//text.setFillColor(sf::Color(191,42,62,255));
				//shape.setFillColor(hover_color);
				break;

			case BTN_ACTIVE:
				text.setOutlineColor(sf::Color(0, 0, 0, 0));
				text.setFillColor(hover_color);
				//shape.setFillColor(active_color);
				break;

			default:
				//shape.setFillColor(sf::Color::Red);
				break;
		}
	}

	void Button::render(sf::RenderTarget* target){
		target->draw(shape);
		target->draw(text);
	}
