#include "stdafx.h"
#include "Button.h"

Button::Button(){
	int y = 0;
}

Button::Button(float x, float y, float width, float height, short text_size, sf::Font* font_
		, string text_, Color btn_hcolor, int id_)
		: btn_hover_color(btn_hcolor), btn_active_color(btn_hcolor), btn_idle_color(Color::White)
		, shp_hover_color(sf::Color(28, 26, 47, 255)), shp_active_color(sf::Color(28, 26, 47, 255))
		, shp_idle_color(sf::Color(28, 26, 47, 255)), position(Vector2f(x, y)), id(id_) {
		ii_type = INTERFACE_ITEM_TYPE::BUTTON;
		button_state = BUTTON_STATE::BTN_IDLE;

		shape.setPosition(position);
		shape.setSize(sf::Vector2f(width, height));

		font = font_;
		text.setFont(*font);
		text.setString(text_);
		text.setFillColor(btn_idle_color);
		text.setCharacterSize(text_size);
		text.setOutlineThickness(3.f);
		text.setOutlineColor(sf::Color(0, 0, 0, 0));
		text.setPosition(
			shape.getPosition().x +(shape.getGlobalBounds().width / 2.f) - text.getLocalBounds().width / 2.f - text.getLocalBounds().left,
			shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getLocalBounds().height / 2.f - text.getLocalBounds().top
			);

		shape.setFillColor(shp_idle_color);
	}

	Button::Button(float x, float y, short text_size, sf::Font* font_, string text_, Color btn_hcolor, int id_)
		: btn_hover_color(btn_hcolor), btn_active_color(btn_hcolor), btn_idle_color(Color::White)
		, shp_hover_color(Color(0, 0, 0, 0)), shp_active_color(Color(0, 0, 0, 0))
		, shp_idle_color(Color(0, 0, 0, 0)), position(Vector2f(x, y)), id(id_) {
		ii_type = INTERFACE_ITEM_TYPE::BUTTON;
		button_state = BUTTON_STATE::BTN_IDLE;

		shape.setPosition(position);
		
		font = font_;
		text.setFont(*font);
		text.setString(text_);
		text.setFillColor(btn_idle_color);
		text.setCharacterSize(text_size);
		text.setOutlineThickness(3.f);
		text.setOutlineColor(sf::Color(0, 0, 0, 0));
		text.setPosition(
			shape.getPosition().x - text.getLocalBounds().left,
			shape.getPosition().y - text.getLocalBounds().top
		);

		shape.setSize(sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height));

		shape.setFillColor(shp_idle_color);
	}

	Button::Button(float x, float y, float width, float height, short text_size, sf::Font* font_
		, string text_, bool outline, int id_)
		: position(Vector2f(x, y)), id(id_) {
		ii_type = INTERFACE_ITEM_TYPE::BUTTON;
		button_state = BUTTON_STATE::BTN_IDLE;

		shape.setPosition(position);
		shape.setSize(sf::Vector2f(width, height));
		if (outline) {
			shape.setOutlineThickness(3.f);
			shape.setOutlineColor(Color::Black);
		}
		font = font_;
		text.setFont(*font);
		text.setString(text_);
		text.setFillColor(btn_idle_color);
		text.setCharacterSize(text_size);
		text.setOutlineThickness(3.f);
		text.setOutlineColor(sf::Color(0, 0, 0, 0));
		text.setPosition(
			shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getLocalBounds().width / 2.f - text.getLocalBounds().left,
			shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getLocalBounds().height / 2.f - text.getLocalBounds().top
		);
		FloatRect g = text.getLocalBounds();
		shape.setFillColor(shp_idle_color);
	}
	
	Button::~Button(){

	}

	float Button::getHeight(){
		return shape.getGlobalBounds().height;
	}

	float Button::getWidth(){
		return shape.getGlobalBounds().width;
	}

	float Button::getTextHeight(){
		return text.getLocalBounds().height;
	}

	float Button::getTextWidth(){
		return text.getLocalBounds().width;
	}

	short* Button::getButtonState(){
		return &button_state;
	}

	const int& Button::getIdentificator() const{
		return id;
	}

	FloatRect Button::getLocalBounds(){
		return FloatRect(position, Vector2f(shape.getLocalBounds().width, shape.getLocalBounds().height));
	}

	FloatRect Button::getGlobalBounds(){
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

	void Button::setPositionX(float x){
		setPosition(Vector2f(x + shape.getOutlineThickness(), position.y));
	}

	void Button::setPositionY(float y){
		setPosition(Vector2f(position.x, y + shape.getOutlineThickness()));
	}

	void Button::changePosition(float offset_x, float offset_y){
		setPosition(Vector2f(position.x + offset_x, position.y + offset_y));
	}

	void Button::setColors(Color btn_hcolor, Color btn_icolor, Color shp_hcolor, Color shp_icolor){
		btn_idle_color = btn_icolor;
		btn_hover_color = btn_hcolor;
		btn_active_color = btn_hcolor;
		shp_idle_color = shp_icolor;
		shp_hover_color = shp_hcolor;
		shp_active_color = shp_hcolor;
	}

	void Button::setBackgroundColor(Color shapeColor){
		shape.setFillColor(shapeColor);
	}

	void Button::resetActiveState(){
		button_state = BUTTON_STATE::BTN_IDLE;
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
				//std::cout << "active" << std::endl;
			}
			else {
				button_state = BUTTON_STATE::BTN_HOVERED;
				//std::cout << "hover" << std::endl;
			}
		}

		switch (button_state) {
			case BTN_IDLE:
				text.setOutlineColor(sf::Color(0, 0, 0, 0));
				text.setFillColor(btn_idle_color);
				shape.setFillColor(shp_idle_color);
				break;

			case BTN_HOVERED:
				text.setOutlineColor(sf::Color(0, 0, 0, 255));
				text.setFillColor(btn_hover_color);
				shape.setFillColor(shp_hover_color);
				break;

			case BTN_ACTIVE:
				text.setOutlineColor(sf::Color(0, 0, 0, 0));
				text.setFillColor(btn_hover_color);
				shape.setFillColor(shp_active_color);
				break;

			default:
				break;
		}
	}

	void Button::render(sf::RenderTarget* target){
		target->draw(shape);
		//if (btn_image != nullptr) {
			//target->draw(*btn_image);
		//}
		target->draw(text);
	}
