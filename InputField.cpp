#include "stdafx.h"
#include "InputField.h"


	InputField::InputField(){
		id = GlobalProcessData::getUnicId();
	}

	InputField::InputField(float x, float y, float width_, float height_, const string& input_label_, 
		 int text_size_)
		:text_size(text_size_), position(Vector2f(x, y)), width(width_), height(height_) {
		ii_type = INTERFACE_ITEM_TYPE::FORM_ITEM;
		fi_state = FORM_ITEM_STATE::FORM_ITEM_IDLE;
		fi_type = FORM_ITEM_TYPE::INPUT_FIELD;
		id = GlobalProcessData::getUnicId();

		chosen = false;
		unpressed = true;
		overflow_x = false;

		shape1.setFillColor(Color(0, 0, 0, 0));
		shape1.setOutlineThickness(1);
		shape1.setOutlineColor(Color::Magenta);
		shape1.setPosition(position.x + 1, position.y + 1);
		shape1.setSize(Vector2f(width - 2, height - 2));

		label = new Text();
		label->setFont(*GlobalProcessData::getFont());
		label->setString(input_label_);
		label->setCharacterSize(20);
		label->setFillColor(Color::White);
		label->setPosition(
			position.x - label->getLocalBounds().left + 5,
			position.y - label->getLocalBounds().top
		);
	}

	InputField::InputField(float x, float y, float width_, float height_, const string& input_label_, 
		 int text_size_, Color text_color_, bool has_limit_, int limit_, bool multiline)
		:InputField(x, y, width_, height_, input_label_, text_size_){
		has_limit = has_limit_;
		limit = limit_;
		textarea = new Textarea(
			position.x,
			position.y + label->getGlobalBounds().height + label->getLocalBounds().top + 6,
			width,
			height - (position.y + label->getGlobalBounds().height + label->getLocalBounds().top + 6 - position.y),
			text_size,
			multiline);
		textarea->setTextColor(text_color_);
	}

	InputField::InputField(float x, float y, float width_, float height_, const string& input_label_,
		 int text_size_, Color text_color_, bool has_limit_, int limit_)
		:InputField(x, y, width_, height_, input_label_, text_size_){
		has_limit = has_limit_;
		limit = limit_;
		textarea = new Textarea(
			position.x,
			position.y + label->getGlobalBounds().height + label->getLocalBounds().top + 6,
			width,
			height - (position.y + label->getGlobalBounds().height + label->getLocalBounds().top + 6 - position.y),
			text_size,
			false);
		textarea->setTextColor(text_color_);
	}
	
	InputField::InputField(float x, float y, float width_, float height_, const string& input_label_, 
		 int text_size_, bool has_limit_, int limit_)
		:InputField(x, y, width_, height_, input_label_, text_size_){
		has_limit = has_limit_;
		limit = limit_;
		textarea = new Textarea(
			position.x,
			position.y + label->getGlobalBounds().height + label->getLocalBounds().top + 6,
			width,
			height - (position.y + label->getGlobalBounds().height + label->getLocalBounds().top + 6 - position.y),
			text_size,
			false);
		textarea->setTextColor(Color::Black);
		textarea->setOverflow(ITEM_OVERFLOW::HIDDEN);
		}

	InputField::~InputField(){
		delete label;
		delete textarea;
	}

	FloatRect InputField::getLocalBounds(){
		return textarea->getGlobalBounds();
	}

	FloatRect InputField::getGlobalBounds(){
		return FloatRect(position, Vector2f(width, height));
	}

	string* InputField::getString(){
		return textarea->getString();
	}

	bool InputField::itemScroll(float delta){
		FloatRect view_cords = GlobalProcessData::getViewCords();
		Vector2f mouse_pos = GlobalProcessData::getMousePos();

		View t_view = textarea->createLocalView(textarea->getLocalBounds(), GlobalProcessData::getWindow());
		FloatRect t_on_screen = FloatRect(
			t_view.getCenter().x - (t_view.getSize().x / 2),
			t_view.getCenter().y - (t_view.getSize().y / 2),
			t_view.getSize().x,
			t_view.getSize().y
		);//FIXME: scrolling while content is not visible

		if (t_on_screen.contains(mouse_pos.x + (view_cords.left - view_cords.width / 2), mouse_pos.y + (view_cords.top - view_cords.height / 2))) {
			if (!textarea->contentOverflows()) {
				return false;
			}
			//std::cout << "1" << std::endl;
			textarea->scroll(delta);
			return true;
		}
		return false;
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
			textarea->setString(input_stream.str());
		}
		else if (typed_char == DELETE_KEY) {
			if (input_stream.str().length() > 0) {
				deletLastChar();
			}
		}
		textarea->addCursor('_');
	}
	
	void InputField::deletLastChar() {
		string tmp = input_stream.str();
		tmp.pop_back();
		input_stream.str("");
		input_stream << tmp;
		textarea->removeLastCharacter();
	}

	void InputField::setOverflow(short overflow){
		textarea->setOverflow(overflow);
	}

	void InputField::setVisibility(bool vis){
		textarea->setVisibility(vis);
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
		label->setPosition(
			position.x - label->getLocalBounds().left + 5,
			position.y - label->getLocalBounds().top
		);

		textarea->changePosition(offset_x, offset_y);
	}

	void InputField::changeVisibility(float param1, float param2){
		if (textarea->getVisibility())
			textarea->setVisibility(false);
		else
			textarea->setVisibility(true);
	}

	void InputField::update(){
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
			view_cords.top - view_cords.height / 2 + position.y + 1
		);

		textarea->update();
	}

	void InputField::render(){
		RenderTarget* target = GlobalProcessData::getWindow();

		target->draw(*label);
		textarea->render();
		target->draw(shape1);
	}
