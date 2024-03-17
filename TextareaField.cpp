#include "stdafx.h"
#include "TextareaField.h"


TextareaField::TextareaField(float x, float y, float width_, float height_, const string& input_label_,
		Font* font_, int text_size_, Color text_color_, bool has_limit_, int limit_)
	: InputField(x, y, width_, height_, input_label_, font_, text_size_, has_limit_, limit_) {

	}
	
	TextareaField::TextareaField(float x, float y, float width_, float height_, const string& input_label_, 
		Font* font_, int text_size_, bool has_limit_, int limit_)
	: InputField(x, y, width_, height_, input_label_, font_, text_size_, has_limit_, limit_) {

	}
	
	void TextareaField::inputLogic(int typed_char){
		if (typed_char != ESCAPE_KEY && typed_char != ENTER_KEY && typed_char != DELETE_KEY) {
			input_stream << static_cast<char>(typed_char);
			*input_str = input_stream.str();
		}
		else if (typed_char == DELETE_KEY) {
			if (input_stream.str().length() > 0) {
				deletLastChar();
			}
		}
		input_text->setString(input_stream.str() + "_");
		if ((input_text->getLocalBounds().width + 10 - input_text->getLocalBounds().left) >
			shape.getGlobalBounds().width) {
			if (!overflow_x) {
				overflow_x = true;
				string tmp = input_stream.str();
				efficient_chars = tmp.length();
				tmp += "\n_";
				input_text->setString(tmp);
			}
			else {
				string tmp = input_stream.str();
				string tmp1 = tmp.substr(0, efficient_chars);
				tmp1 += "\n";
				tmp1 += tmp.substr(efficient_chars, tmp.length());
				input_text->setString(tmp1);
			}
		}
		else {
			overflow_x = false;
			efficient_chars = 0;
		}

	}
	void TextareaField::update(Vector2f mouse_pos, FloatRect view_cords){
		//if (fi_state == FORM_ITEM_STATE::FORM_ITEM_IDLE && !overflow_y) {
		//	input_text->setString(input_stream.str());
		//}
		//else if (fi_state == FORM_ITEM_STATE::FORM_ITEM_ACTIVE_1 && !overflow_y) {
		//	input_text->setString(input_stream.str() + "_");
		//}

		if (shape.getGlobalBounds().contains(mouse_pos.x + (view_cords.left - view_cords.width / 2), mouse_pos.y + (view_cords.top - view_cords.height / 2))) {
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

		switch (fi_state) {
		case FORM_ITEM_IDLE:
			shape.setOutlineColor(Color(60, 60, 118, 255));
			break;

		case FORM_ITEM_HOVERED:
			shape.setOutlineColor(Color(60, 60, 118, 255));
			break;

		case FORM_ITEM_ACTIVE_1:
			shape.setOutlineColor(Color::Green);
			break;

		default:
			break;
		}

		shape1.setPosition(
			view_cords.left - view_cords.width / 2 + position.x + 1,
			view_cords.top - view_cords.height / 2 + position.y + 1);
		input_label->setPosition(
			view_cords.left - view_cords.width / 2 + position.x - input_label->getLocalBounds().left + 5,
			view_cords.top - view_cords.height / 2 + position.y - input_label->getLocalBounds().top
		);
		shape.setPosition(
			view_cords.left - view_cords.width / 2 + position.x + 2,
			view_cords.top - view_cords.height / 2 + position.y + input_label->getGlobalBounds().height + input_label->getLocalBounds().top + 2 + 6
		);

		string tmp = input_text->getString();
		input_text->setString("a");
		input_text->setPosition(
			view_cords.left - view_cords.width / 2 + position.x + 10 - input_text->getLocalBounds().left,//left offset
			view_cords.top - view_cords.height / 2 + shape.getPosition().y + (shape.getGlobalBounds().height - input_text->getGlobalBounds().height) / 2.f - input_text->getLocalBounds().top
		);
		input_text->setString(tmp);
	}
