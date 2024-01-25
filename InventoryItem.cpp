#include "stdafx.h"
#include "InventoryItem.h"

	InventoryItem::InventoryItem(float x, float y, float width_, float height_, int text_size_, Font* font)
		:position(Vector2f(x, y)), width(width_), height(height_), text_size(text_size_){
		image = new BasicImage(x, y);
		r_info = new ResourceInfo(x, y + height - 20, font, text_size_, false);
		text.setFont(*font);
		text.setCharacterSize(text_size);

		text.setPosition(
			position.x,
			position.y + height
		);
	}

	void InventoryItem::addItemInfo(TextureManager* t_manager, Warehouse* w_object, string name){
		image->addInfo(t_manager, w_object, name);

		short scale = (width / image->getLocalBounds().width);
		image->setScale(scale);
		image->setPosition(
			position.x + (width - image->getGlobalBounds().width) / 2,
			position.y + (width - image->getGlobalBounds().height) / 2
		);

		text.setString(w_object->getWarehouseItem(name)->getNameFU());
		text.setFillColor(Color::White);
		text.setPosition(Vector2f(
			position.x + width - r_info->getGlobalBounds().width,
			position.y + width - r_info->getGlobalBounds().height
		));

		r_info->addInfo(t_manager, w_object, name, true);
		r_info->setPosition(Vector2f(
			position.x + width - r_info->getGlobalBounds().width,
			text.getGlobalBounds().top - r_info->getGlobalBounds().height
		));
	}

	void InventoryItem::addItemInfo(TextureManager* t_manager, WarehouseItem* w_item){
		image->addInfo(t_manager, w_item);

		short scale = (width / image->getLocalBounds().width);
		image->setScale(scale);
		image->setPosition(
			position.x + (width - image->getGlobalBounds().width) / 2,
			position.y + (width - image->getGlobalBounds().height) / 2
		);
		image->setBColor(Color::Magenta);

		text.setString(w_item->getNameFU());
		text.setFillColor(Color::White);
		text.setPosition(Vector2f(
			position.x + width - r_info->getGlobalBounds().width,
			position.y + width - r_info->getGlobalBounds().height
		));

		r_info->addInfo(t_manager, w_item, true);
		r_info->setPosition(Vector2f(
			position.x + width - r_info->getGlobalBounds().width,
			text.getGlobalBounds().top - r_info->getGlobalBounds().height
		));
	}

	FloatRect InventoryItem::getLocalBounds(){
		return FloatRect(position, Vector2f(width, height));
	}

	FloatRect InventoryItem::getGlobalBounds(){
		return FloatRect(position, Vector2f(width, height));
	}

	void InventoryItem::setPosition(Vector2f new_position){
		position = new_position;
		image->setPosition(
			position.x + (width - image->getGlobalBounds().width) / 2,
			position.y + (width - image->getGlobalBounds().height) / 2
		);

		text.setPosition(Vector2f(
			position.x + (width - text.getGlobalBounds().width)/2,
			position.y + width - text.getGlobalBounds().height
		));

		r_info->setPosition(Vector2f(
			position.x + (width - r_info->getGlobalBounds().width)/2,
			text.getGlobalBounds().top - r_info->getGlobalBounds().height - text.getGlobalBounds().height
		));
	}

	void InventoryItem::setPositionX(float x){
		setPosition(Vector2f(x, position.y));
	}

	void InventoryItem::setPositionY(float y){
		setPosition(Vector2f(position.x, y));
	}

	void InventoryItem::changePosition(float offset_x, float offset_y){
		setPosition(Vector2f(position.x + offset_x, position.y + offset_y));
	}

	void InventoryItem::update(Vector2f mouse_pos, FloatRect view_cords){
		image->update(mouse_pos, view_cords);
		r_info->update(mouse_pos, view_cords);
		//text.setPosition();
	}

	void InventoryItem::render(RenderTarget* target){
		image->render(target);
		r_info->render(target);
		target->draw(text);
	}
