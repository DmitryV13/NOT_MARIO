#include "stdafx.h"
#include "InputField.h"


	InputField::InputField(float x, float y, float width_, float height_, const string& input_label_, 
		Font* font_, int text_size_, Color text_color_, bool has_limit_, int limit_)
		:text_size(text_size_), text_color(text_color_), has_limit(has_limit_), limit(limit_)
		, position(Vector2f(x, y)), width(width_), height(height_) {
		ii_type = INTERFACE_ITEM_TYPE::FORM_ITEM;
		fi_state = FORM_ITEM_STATE::FORM_ITEM_IDLE;
		fi_type = FORM_ITEM_TYPE::INPUT_FIELD;
		chosen = false;
		unpressed = true;
		overflow_x = false;
		input_str = new string();

		shape1.setFillColor(Color(0, 0, 0, 0));
		shape1.setOutlineThickness(1);
		shape1.setOutlineColor(Color::Green);
		shape1.setPosition(position.x + 1, position.y + 1);
		shape1.setSize(Vector2f(width - 2, height - 2));

		input_label = new Text();
		input_label->setFont(*font_);
		input_label->setString(input_label_);
		input_label->setCharacterSize(20);
		input_label->setFillColor(Color::White);
		input_label->setPosition(
			position.x - input_label->getLocalBounds().left + 5,
			position.y - input_label->getLocalBounds().top
		);

		shape.setSize(Vector2f(
			width - 4,
			height - 4 - 6 - input_label->getGlobalBounds().height - input_label->getLocalBounds().top)
		);
		shape.setPosition(
			position.x + 2,
			position.y + input_label->getGlobalBounds().height + input_label->getLocalBounds().top + 2 + 6
		);//top offset
		shape.setFillColor(Color::White);
		shape.setOutlineThickness(2);
		shape.setOutlineColor(Color(60, 60, 118, 255));

		input_text = new Text();
		input_text->setFont(*font_);
		input_text->setString("a");
		input_text->setCharacterSize(text_size);
		input_text->setFillColor(text_color);
		input_text->setPosition(
			position.x + 10 - input_text->getLocalBounds().left,//left offset
			shape.getPosition().y + (shape.getGlobalBounds().height - input_text->getGlobalBounds().height) / 2.f - input_text->getLocalBounds().top
		);
		input_text->setString("");
		}
	
	InputField::InputField(float x, float y, float width_, float height_, const string& input_label_, 
		Font* font_, int text_size_, bool has_limit_, int limit_)
		:text_size(text_size_), text_color(Color::Black), has_limit(has_limit_), limit(limit_)
		, position(Vector2f(x, y)), width(width_), height(height_) {
			ii_type = INTERFACE_ITEM_TYPE::FORM_ITEM;
			fi_state = FORM_ITEM_STATE::FORM_ITEM_IDLE;
			fi_type = FORM_ITEM_TYPE::INPUT_FIELD;
			chosen = false;
			unpressed = true;
			overflow_x = false;
			input_str = new string();

			shape1.setFillColor(Color(0, 0, 0, 0));
			shape1.setOutlineThickness(1);
			shape1.setOutlineColor(Color::Green);
			shape1.setPosition(position.x + 1, position.y + 1);
			shape1.setSize(Vector2f(width - 2, height - 2));

			input_label = new Text();
			input_label->setFont(*font_);
			input_label->setString(input_label_);
			input_label->setCharacterSize(20);
			input_label->setFillColor(Color::White);
			input_label->setPosition(
				position.x - input_label->getLocalBounds().left + 5,
				position.y - input_label->getLocalBounds().top
			);

			shape.setSize(Vector2f(
				width - 4,
				height - 4 - 6 - input_label->getGlobalBounds().height - input_label->getLocalBounds().top)
			);
			shape.setPosition(
				position.x + 2, 
				position.y + input_label->getGlobalBounds().height + input_label->getLocalBounds().top + 2 + 6
			);//top offset
			shape.setFillColor(Color::White);
			shape.setOutlineThickness(2);
			shape.setOutlineColor(Color(60, 60, 118, 255));

			input_text = new Text();
			input_text->setFont(*font_);
			input_text->setString("a");
			input_text->setCharacterSize(text_size);
			input_text->setFillColor(text_color);
			input_text->setPosition(
				position.x + 10 - input_text->getLocalBounds().left,//left offset
				shape.getPosition().y + (shape.getGlobalBounds().height - input_text->getGlobalBounds().height)/2.f - input_text->getLocalBounds().top
			);
			input_text->setString("");
		}

	FloatRect InputField::getLocalBounds(){
		return shape.getGlobalBounds();
	}

	FloatRect InputField::getGlobalBounds(){
		return FloatRect(position, Vector2f(width, height));
	}

	string* InputField::getSource(){
		return input_str;
	}

	void InputField::formEInput(Event event) {
		if (fi_state == FORM_ITEM_STATE::FORM_ITEM_ACTIVE_1) {
			int typed_char = event.text.unicode;
			//verification that char is valid
			if (has_limit) {
				if (input_stream.str().length() < limit) {
					inputLogic(typed_char);
				}
				else if (input_stream.str().length() >= limit && typed_char == DELETE_KEY) {
					deletLastChar();
				}
			}
			else {
				inputLogic(typed_char);
			}
		}
	}
	
	void InputField::inputLogic(int typed_char) {
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
		if ((input_text->getGlobalBounds().width + 10 + input_text->getLocalBounds().left) > 
			shape.getSize().x) {
			if (!overflow_x) {
				overflow_x = true;
				string tmp = input_stream.str();
				efficient_chars = tmp.length();
				input_text->setString(tmp);
			}else{
				string tmp = input_stream.str();
				string tmp1 = tmp.substr(0, efficient_chars);
				input_text->setString(tmp1);
			}
		}
		else {
			overflow_x = false;
			efficient_chars = 0;
		}

	}
	
	void InputField::deletLastChar() {
		string tmp = input_stream.str();
		tmp.pop_back();
		input_stream.str("");
		input_stream << tmp;
		*input_str = input_stream.str();
	}
	
	void InputField::setPositionX(float x){
		float offset = x - position.x;
		changePosition(offset, 0);
	}

	void InputField::setPositionY(float y){
		float offset = y - position.y;
		changePosition(0, offset);
	}

	void InputField::changePosition(float offset_x, float offset_y){
		position.x += offset_x;
		position.y += offset_y;

		shape1.setPosition(position.x + 1, position.y + 1);
		input_label->setPosition(
			position.x - input_label->getLocalBounds().left + 5,
			position.y - input_label->getLocalBounds().top
		);
		shape.setPosition(
			position.x + 2,
			position.y + input_label->getGlobalBounds().height + input_label->getLocalBounds().top + 2 + 6
		);
		string tmp = input_text->getString();
		input_text->setString("a");
		input_text->setPosition(
			position.x + 10 - input_text->getLocalBounds().left,//left offset + border
			shape.getPosition().y + (shape.getGlobalBounds().height - input_text->getGlobalBounds().height) / 2.f - input_text->getLocalBounds().top
		);
		input_text->setString(tmp);
	}

	void InputField::update(Vector2f mouse_pos, FloatRect view_cords){
		if (fi_state == FORM_ITEM_STATE::FORM_ITEM_IDLE && !overflow_x) {
			input_text->setString(input_stream.str());
		}
		else if (fi_state == FORM_ITEM_STATE::FORM_ITEM_ACTIVE_1 && !overflow_x) {
			input_text->setString(input_stream.str()+"_");
		}

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

	void InputField::render(sf::RenderTarget* target){
		target->draw(*input_label);
		target->draw(shape);
		target->draw(*input_text);
		//target->draw(shape1);
	}
