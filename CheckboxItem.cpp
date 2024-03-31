#include "stdafx.h"
#include "CheckboxItem.h"

	CheckboxItem::CheckboxItem(float x, float y, float width_, float height_, int text_size_)
		:InventoryItem(x, y, width_, height_, text_size_) {
		visible = true;
		ii_type = INTERFACE_ITEM_TYPE::FORM_ITEM;
		fi_state = FORM_ITEM_STATE::FORM_ITEM_IDLE;
		fi_type = FORM_ITEM_TYPE::CHECKBOX_ITEM;
		chosen = false;
		unpressed = true;
		shape.setOutlineThickness(1.f);
	}

	void CheckboxItem::setVisibility(bool visibility){
		visible = visibility;
	}

	void CheckboxItem::update(){
		Vector2f mouse_pos = GlobalProcessData::getMousePos();
		FloatRect view_cords = GlobalProcessData::getViewCords();

		FloatRect gr =
			FloatRect(
				getGlobalBounds().left + view_cords.left - view_cords.width / 2,
				getGlobalBounds().top + view_cords.top - view_cords.height / 2,
				getGlobalBounds().width,
				getGlobalBounds().height);
		if (gr.contains(mouse_pos.x + (view_cords.left - view_cords.width / 2)
			, mouse_pos.y + (view_cords.top - view_cords.height / 2))) {
			//fi_state = FORM_ITEM_STATE::FORM_ITEM_HOVERED;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (unpressed) {
					if (!chosen) {
						chosen = true;
						fi_state = FORM_ITEM_STATE::FORM_ITEM_ACTIVE_1;
						//std::cout << "active" << std::endl;
					}
					else {
						chosen = false;
						fi_state = FORM_ITEM_STATE::FORM_ITEM_IDLE;
						//std::cout << "idle" << std::endl;
					}
					unpressed = false;
				}
			}
			if (!Mouse::isButtonPressed(sf::Mouse::Left)) {
				unpressed = true;
			}
			std::cout << fi_state << std::endl;
		}

		//if (fi_state == FORM_ITEM_STATE::FORM_ITEM_ACTIVE_1) {
		//	std::cout << "active____1" << std::endl;
		//}
		//if (fi_state == FORM_ITEM_STATE::FORM_ITEM_ACTIVE_2) {
		//	std::cout << "active____2" << std::endl;
		//}
		//if (fi_state == FORM_ITEM_STATE::FORM_ITEM_IDLE) {
		//	std::cout << "idle" << std::endl;
		//}

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

		////////////////////////////////////

		shape.setPosition(position.x + 1, position.y + 1);
		image->update();
		r_info->update();
		text.setPosition(Vector2f(
			view_cords.left - view_cords.width / 2 + position.x + (width - text.getGlobalBounds().width) / 2,
			view_cords.top - view_cords.height / 2 + position.y + width - text.getGlobalBounds().height
		));
		shape.setPosition(
			view_cords.left - view_cords.width / 2 + position.x + 1,
			view_cords.top - view_cords.height / 2 + position.y + 1
		);
		background.setPosition(
			view_cords.left - view_cords.width / 2 + position.x,
			view_cords.top - view_cords.height / 2 + position.y
		);
	}

	void CheckboxItem::render(){
		RenderTarget* target = GlobalProcessData::getWindow();
		
		target->draw(background);
		//if (visible) {
			image->render();
			r_info->render();
			target->draw(text);
		//}
		target->draw(shape);
		//std::cout << "check   " << text.getGlobalBounds().left << "   " << text.getGlobalBounds().top << std::endl;
	}
