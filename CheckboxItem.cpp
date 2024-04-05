#include "stdafx.h"
#include "CheckboxItem.h"

	CheckboxItem::CheckboxItem(float x, float y, float width_, float height_)
		:Group(x, y, width_, height_) {
		ii_type = INTERFACE_ITEM_TYPE::FORM_ITEM;
		fi_state = FORM_ITEM_STATE::FORM_ITEM_IDLE;
		fi_type = FORM_ITEM_TYPE::CHECKBOX_ITEM;
		chosen = false;
		unpressed = true;
		shape.setOutlineThickness(1.f);
		shape.setFillColor(Color(0, 0, 0, 0));
		shape.setPosition(x + 1, y + 1);
		shape.setSize(Vector2f(width_ - 2, height_ - 2));

		idle_value = "_false_";
		active_value = "_true_";
		value = new string();
		*value = idle_value;
	}

	CheckboxItem::~CheckboxItem(){
	}

	string* CheckboxItem::getValue(){
		return value;
	}

	void CheckboxItem::setValue(string val){
		active_value = val;
	}

	void CheckboxItem::update(){
		Group::update();

		Vector2f mouse_pos = GlobalProcessData::getMousePos();
		FloatRect view_cords = GlobalProcessData::getViewCords();

		shape.setPosition(position.x + 1, position.y + 1);
		shape.setPosition(view_cords.left - view_cords.width / 2 + shape.getPosition().x,
			view_cords.top - view_cords.height / 2 + shape.getPosition().y
		);

		FloatRect group_bounds =
			FloatRect(
				getGlobalBounds().left + view_cords.left - view_cords.width / 2,
				getGlobalBounds().top + view_cords.top - view_cords.height / 2,
				getGlobalBounds().width,
				getGlobalBounds().height);
		if (group_bounds.contains(mouse_pos.x + (view_cords.left - view_cords.width / 2)
			, mouse_pos.y + (view_cords.top - view_cords.height / 2))) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (unpressed) {
					if (!chosen) {
						chosen = true;
						fi_state = FORM_ITEM_STATE::FORM_ITEM_ACTIVE_1;
						*value = active_value;
					}
					else {
						chosen = false;
						fi_state = FORM_ITEM_STATE::FORM_ITEM_IDLE;
						*value = idle_value;
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
			shape.setOutlineColor(Color(0, 0, 0, 0));
			break;

		case FORM_ITEM_HOVERED:
			shape.setOutlineColor(Color(0, 0, 0, 0));
			break;

		case FORM_ITEM_ACTIVE_1:
			shape.setOutlineColor(Color::Green);
			break;

		default:
			break;
		}
	}

	void CheckboxItem::render(){
		Group::render();
		RenderWindow* target = GlobalProcessData::getWindow();
		target->draw(shape);
	}
