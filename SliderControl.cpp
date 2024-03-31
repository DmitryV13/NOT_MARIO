#include "stdafx.h"
#include "SliderControl.h"


SliderControl::SliderControl(float x, float y, float width_, float height_, const string& input_label_)
		:position(Vector2f(x, y)), width(width_), height(height_) {
		ii_type = INTERFACE_ITEM_TYPE::FORM_ITEM;
		id = GlobalProcessData::getUnicId();
		fi_state = FORM_ITEM_STATE::FORM_ITEM_IDLE;
		fi_type = FORM_ITEM_TYPE::SLIDER_CONTROL;

		chosen = false;
		mouse_pressed_pos_x = 0;

		label = new Text();
		label->setFont(*GlobalProcessData::getFont());
		label->setString(input_label_);
		label->setCharacterSize(20);
		label->setFillColor(Color::White);
		label->setPosition(
			position.x - label->getLocalBounds().left + 5,
			position.y - label->getLocalBounds().top
		);

		shape1.setFillColor(Color(0, 0, 0, 0));
		shape1.setOutlineThickness(1);
		shape1.setOutlineColor(Color::Magenta);
		shape1.setPosition(position.x + 1, position.y + 1);
		shape1.setSize(Vector2f(width - 2, height - 2));

		slider.setFillColor(Color(9, 196, 33, 255));
		slider.setOutlineThickness(8);
		slider.setOutlineColor(Color::White);
		slider.setRadius(
			(height - 16 - (position.y + label->getGlobalBounds().height + label->getLocalBounds().top + 20 - position.y)) / 2.f
		);
		slider.setPosition(
			position.x + 8, 
			position.y + 8 + label->getGlobalBounds().height + label->getLocalBounds().top + 20
		);

		scale.setFillColor(Color(9, 196, 33, 255));
		scale.setOutlineThickness(2);
		scale.setOutlineColor(Color::White);
		scale.setSize(Vector2f(
			width - 4, 
			12
		));
		scale.setPosition(
			position.x + 2,
			slider.getPosition().y + 
			(slider.getGlobalBounds().height - slider.getOutlineThickness() - scale.getGlobalBounds().height - scale.getOutlineThickness()) / 2.f
		);
	}
	
	FloatRect SliderControl::getLocalBounds(){
		return FloatRect(
			position.x + 8,
			position.y + 8 + label->getGlobalBounds().height + label->getLocalBounds().top + 6,
			scale.getGlobalBounds().width,
			slider.getGlobalBounds().height
		);
	}
	
	FloatRect SliderControl::getGlobalBounds(){
		return FloatRect(position, Vector2f(width, height));
	}
	
	void SliderControl::setMinMaxType(float min_, float max_){
		min = min_;
		max = max_;
	}

	void SliderControl::setValueType(float* value_, bool isStatic_){
		isStatic = isStatic_;
		if (isStatic) {
			s_value = "";
			delete value_;
		}
		else {
			f_value = value_;
		}
	}
	
	void SliderControl::setPositionX(float x){
		float offset = x - position.x;
		changePosition(offset, 0);
	}
	
	void SliderControl::setPositionY(float y){
		float offset = y - position.y;
		changePosition(0, offset);
	}
	
	void SliderControl::changePosition(float offset_x, float offset_y){
		position.x += offset_x;
		position.y += offset_y;

		label->setPosition(
			position.x - label->getLocalBounds().left + 5,
			position.y - label->getLocalBounds().top
		);
		slider.setPosition(
			position.x + 8,
			position.y + 8 + label->getGlobalBounds().height + label->getLocalBounds().top + 20
		);
		scale.setPosition(
			position.x + 2,
			slider.getPosition().y + 
			(slider.getGlobalBounds().height - slider.getOutlineThickness() - scale.getGlobalBounds().height - scale.getOutlineThickness()) / 2.f
		);
	}

	void SliderControl::scrollSlider(float mouse_current_pos_x){
		float offset = mouse_current_pos_x - mouse_pressed_pos_x;
		if (offset > 0) {
			if ((position.x + width) 
				>= slider.getPosition().x + offset + slider.getGlobalBounds().width - slider.getOutlineThickness()) {
				slider_offset_x += offset;
			}
			else {
				slider_offset_x = width - slider.getGlobalBounds().width;
			}
		}
		if (mouse_current_pos_x < mouse_pressed_pos_x) {
			if (position.x <= slider.getPosition().x + offset - slider.getOutlineThickness()) {
				slider_offset_x += offset;
			}
			else {
				slider_offset_x = 0;
			}
		}
		mouse_pressed_pos_x = mouse_current_pos_x;
	}
	
	void SliderControl::changeValue(){
		float initial_value_offset = min;
		float full_value_range = max - min;
		float full_scale_range = (position.x + width - slider.getGlobalBounds().width) - (position.x);
		float value_one_percent = full_value_range / 100;
		float current_percent = 100 * (slider.getPosition().x - position.x - slider.getOutlineThickness()) / full_scale_range;
		float rezult = current_percent * value_one_percent + initial_value_offset;
		if (isStatic) {
			s_value = std::to_string(rezult);
		}
		else {
			*f_value = rezult;
		}
	}

	void SliderControl::update(){
		Vector2f mouse_pos = GlobalProcessData::getMousePos();
		FloatRect view_cords = GlobalProcessData::getViewCords();

		float mouse_current_pos_x = mouse_pos.x + (view_cords.left - view_cords.width / 2);
		if (slider.getGlobalBounds().contains(mouse_pos.x + (view_cords.left - view_cords.width / 2), mouse_pos.y + (view_cords.top - view_cords.height / 2))) {
			if (Mouse::isButtonPressed(sf::Mouse::Left) && !chosen) {
				chosen = true;
				fi_state = FORM_ITEM_STATE::FORM_ITEM_ACTIVE_1;
				mouse_pressed_pos_x = mouse_pos.x + (view_cords.left - view_cords.width / 2);
			}
			else if(!Mouse::isButtonPressed(sf::Mouse::Left) && chosen){
				fi_state = FORM_ITEM_STATE::FORM_ITEM_IDLE;
				chosen = false;
				mouse_pressed_pos_x = 0.f;
			}
		}
		else if(!getGlobalBounds().contains(mouse_pos.x + (view_cords.left - view_cords.width / 2), mouse_pos.y + (view_cords.top - view_cords.height / 2))){
			fi_state = FORM_ITEM_STATE::FORM_ITEM_IDLE;
			chosen = false;
			mouse_pressed_pos_x = 0.f;
		}
		switch (fi_state) {
		case FORM_ITEM_IDLE:
			break;

		case FORM_ITEM_HOVERED:
			break;

		case FORM_ITEM_ACTIVE_1:
			scrollSlider(mouse_current_pos_x);
			break;
		}
		//std::cout << position.x + slider.getOutlineThickness()<< "  -  " << position.x + width - slider.getGlobalBounds().width << "  -  "<<slider.getPosition().x<< std::endl;
		label->setPosition(
			view_cords.left - view_cords.width / 2 + position.x - label->getLocalBounds().left + 5,
			view_cords.top - view_cords.height / 2 + position.y - label->getLocalBounds().top
		);
		slider.setPosition(
			view_cords.left - view_cords.width / 2 + position.x + 8 + slider_offset_x,
			view_cords.top - view_cords.height / 2 + position.y + 8 + label->getGlobalBounds().height + label->getLocalBounds().top + 20
		);
		scale.setPosition(
			view_cords.left - view_cords.width / 2 + position.x + 2,
			view_cords.top - view_cords.height / 2 + slider.getPosition().y + 
			(slider.getGlobalBounds().height - slider.getOutlineThickness() - scale.getGlobalBounds().height - scale.getOutlineThickness()) / 2.f
		);
		shape1.setPosition(
			view_cords.left - view_cords.width / 2 + position.x + 1,
			view_cords.top - view_cords.height / 2 + position.y + 1
		);
		changeValue();
	}
	
	void SliderControl::render(){
		RenderTarget* target = GlobalProcessData::getWindow();

		target->draw(*label);
		target->draw(scale);
		target->draw(slider);
		target->draw(shape1);
	}
	