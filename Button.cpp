#include "stdafx.h"
#include "Button.h"

	Button::Button(float x, float y, float width, float height, short text_size, sf::Font* font_, string text_, Color menuColor)
	:hover_color(menuColor){
		button_state = BUTTON_STATE::BTN_IDLE;

		shape.setPosition(sf::Vector2f(x, y));
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

		//shape.setFillColor(idle_color);
	}

	Button::Button(float x, float y, short text_size, sf::Font* font_, string text_, Color menuColor)
	:hover_color(menuColor) {
		button_state = BUTTON_STATE::BTN_IDLE;

		shape.setPosition(sf::Vector2f(x, y));

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
		return text.getLocalBounds().height;
	}

	float Button::getWidth(){
		return text.getLocalBounds().width;
	}

	void Button::setPosition(Vector2f new_pos){
		shape.setPosition(new_pos);
		text.setPosition(new_pos.x-text.getLocalBounds().left, new_pos.y - text.getLocalBounds().top);
	}

	const bool Button::isPressed() const{
		if (button_state == BUTTON_STATE::BTN_ACTIVE)
			return true;
		return false;
	}
	
	void Button::update(const sf::Vector2f mouse_pos, FloatRect view_cords){
		button_state = BUTTON_STATE::BTN_IDLE;
		//std::cout <<"x : "<< mouse_pos.x + (view_cords.left - view_cords.width / 2) << " ,y : " << mouse_pos.y + (view_cords.top - view_cords.height / 2) << std::endl;
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
				//shape.setFillColor(idle_color);
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
