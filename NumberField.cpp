#include "stdafx.h"
#include "NumberField.h"

	NumberField::NumberField(float x, float y, float width_, float height_, const string& input_label_, 
		 int text_size_, Color text_color_, bool has_limit_, int limit_)
		:InputField(x, y, width_, height_, input_label_, text_size_, Color::Black, has_limit_, limit_, false) {
		fi_type = FORM_ITEM_TYPE::NUMBER_FIELD;

		textarea->setOverflow(ITEM_OVERFLOW::HIDDEN);
	}
	
	NumberField::NumberField(float x, float y, float width_, float height_, const string& input_label_, 
		 int text_size_, bool has_limit_, int limit_)
		:InputField(x, y, width_, height_, input_label_, text_size_, Color::Black, has_limit_, limit_, false) {
		fi_type = FORM_ITEM_TYPE::NUMBER_FIELD;

		textarea->setOverflow(ITEM_OVERFLOW::HIDDEN);
	}

	NumberField::~NumberField(){
	}

	void NumberField::inputLogic(int typed_char){
		if (typed_char != ESCAPE_KEY && typed_char != ENTER_KEY && typed_char != DELETE_KEY) {
			if (47 < typed_char && typed_char < 58) {
				input_stream << static_cast<char>(typed_char);
				textarea->setString(input_stream.str());
			}
		}
		else if (typed_char == DELETE_KEY) {
			if (input_stream.str().length() > 0) {
				deletLastChar();
			}
		}
		textarea->addCursor('_');
	}

	void NumberField::setMinMaxType(float min_, float max_, bool isFloat_){
		min = min_;
		max = max_;
		isFloat = isFloat_;
		textarea->setString(isFloat ? std::to_string(min) : std::to_string(static_cast<int>(min)));
		input_stream.str("");
		input_stream << min;
	}

	void NumberField::update(){
		Vector2f mouse_pos = GlobalProcessData::getMousePos();
		FloatRect view_cords = GlobalProcessData::getViewCords();

		if (textarea->getGlobalBounds().contains(mouse_pos.x + (view_cords.left - view_cords.width / 2), mouse_pos.y + (view_cords.top - view_cords.height / 2))) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (unpressed) {
					if (!chosen) {
						chosen = true;
						fi_state = FORM_ITEM_STATE::FORM_ITEM_ACTIVE_1;
					}
					else {
						chosen = false;
						fi_state = FORM_ITEM_STATE::FORM_ITEM_IDLE;
					}
					unpressed = false;
				}
			}
			if (!Mouse::isButtonPressed(sf::Mouse::Left)) {
				unpressed = true;
			}
		}

		if (fi_state == FORM_ITEM_STATE::FORM_ITEM_ACTIVE_1) {
			if (!textarea->hasCursor()) {
				textarea->addCursor('_');
			}
		}
		else {
			if (textarea->hasCursor()) {
				textarea->removeCursor();
				string* tmp = textarea->getString();
				if (!tmp->empty()) {
					if (std::stof(*tmp) < min) {
						textarea->setString(isFloat ? std::to_string(min) : std::to_string(static_cast<int>(min)));
						input_stream.str("");
						input_stream << min;
					}
					else if (std::stof(*tmp) > max) {
						textarea->setString(isFloat ? std::to_string(max) : std::to_string(static_cast<int>(max)));
						input_stream.str("");
						input_stream << max;
					}
				}
				else {
					textarea->setString(isFloat ? std::to_string(min) : std::to_string(static_cast<int>(min)));
					input_stream.str("");
					input_stream << isFloat ? std::to_string(min) : std::to_string(static_cast<int>(min));
				}
			}
		}

		switch (fi_state) {
		case FORM_ITEM_IDLE:
			textarea->setOutlineColor(Color(60, 60, 118, 255));
			break;

		case FORM_ITEM_HOVERED:
			textarea->setOutlineColor(Color(60, 60, 118, 255));
			break;

		case FORM_ITEM_ACTIVE_1:
			textarea->setOutlineColor(Color::Green);
			break;

		default:
			break;
		}

		label->setPosition(
			view_cords.left - view_cords.width / 2 + position.x - label->getLocalBounds().left + 5,
			view_cords.top - view_cords.height / 2 + position.y - label->getLocalBounds().top
		);
		shape1.setPosition(
			view_cords.left - view_cords.width / 2 + position.x + 1,
			view_cords.top - view_cords.height / 2 + position.y + 1);

		textarea->update();
	}