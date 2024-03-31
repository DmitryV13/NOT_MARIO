#include "stdafx.h"
#include "InventoryItem.h"

	InventoryItem::InventoryItem(float x, float y, float width_, float height_, int text_size_)
		:position(Vector2f(x, y)), width(width_), height(height_), text_size(text_size_){
		id = GlobalProcessData::getUnicId();
		background.setPosition(x, y);
		background.setSize(Vector2f(width, height));
		background.setFillColor(Color(0, 0, 0, 0));

		shape.setPosition(x+1, y+1);
		shape.setSize(Vector2f(width-2, height-2));
		shape.setFillColor(Color(0, 0, 0, 0));

		image = new BasicImage(x, y);
		r_info = new ResourceInfo(x, y + height - 20, text_size_, false);
		text.setFont(*GlobalProcessData::getFont());
		text.setCharacterSize(text_size);

		text.setPosition(
			position.x,
			position.y + height
		);
	}

	void InventoryItem::addItemInfo(TextureManager* t_manager, Warehouse* w_object, string name){
		image = new BasicImage(position.x, position.y);
		r_info = new ResourceInfo(position.x, position.y + height - 20, (int)text.getCharacterSize(), false);
		image->addInfo(t_manager, w_object, name);

		float scale = (width / image->getLocalBounds().width) <
			(width / image->getLocalBounds().height) ?
			(width / image->getLocalBounds().width) :
			(width / image->getLocalBounds().height);
		image->setScale(scale);
		image->setPosition(
			position.x + (width - image->getGlobalBounds().width) / 2,
			position.y + (width - image->getGlobalBounds().height) / 2
		);
		string h = w_object->getWarehouseItem(name)->getNameFU();
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

		float scale = (width / image->getLocalBounds().width) <
			(width / image->getLocalBounds().height) ?
			(width / image->getLocalBounds().width) :
			(width / image->getLocalBounds().height);

		image->setScale(scale);
		image->setPosition(
			position.x + (width - image->getGlobalBounds().width) / 2,
			position.y + (width - image->getGlobalBounds().height) / 2
		);
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

	void InventoryItem::clearInfo(){
		text.setString("");
		delete image;
		delete r_info;
		image = new BasicImage(position.x, position.y);
		r_info = new ResourceInfo(position.x, position.y + height - 20, (int)text.getCharacterSize(), false);
	}

	FloatRect InventoryItem::getLocalBounds(){
		return FloatRect(position, Vector2f(width, height));
	}

	FloatRect InventoryItem::getGlobalBounds(){
		return FloatRect(position, Vector2f(width, height));
	}

	void InventoryItem::setPosition(Vector2f new_position){
		background.setPosition(new_position.x, new_position.y);
		shape.setPosition(new_position.x + 1, new_position.y + 1);
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

	void InventoryItem::setBColor(Color color){
		background.setFillColor(color);
	}

	void InventoryItem::changePosition(float offset_x, float offset_y){
		setPosition(Vector2f(position.x + offset_x, position.y + offset_y));
	}

	void InventoryItem::update(){
		Vector2f mouse_pos = GlobalProcessData::getMousePos();
		FloatRect view_cords = GlobalProcessData::getViewCords();

		background.setPosition(position.x, position.y);
		shape.setPosition(position.x + 1, position.y + 1);
		image->update();
		r_info->update();
		text.setPosition(Vector2f(
			view_cords.left-view_cords.width / 2 + position.x + (width - text.getGlobalBounds().width) / 2,
			view_cords.top - view_cords.height / 2 + position.y + width - text.getGlobalBounds().height
		));
		background.setPosition(view_cords.left - view_cords.width / 2 + background.getPosition().x,
			view_cords.top - view_cords.height / 2 + background.getPosition().y
		);
		background.setPosition(view_cords.left - view_cords.width / 2 + background.getPosition().x,
			view_cords.top - view_cords.height / 2 + background.getPosition().y
		);
	}

	void InventoryItem::render(){
		RenderTarget* target = GlobalProcessData::getWindow();

		target->draw(background);
		image->render();
		r_info->render();
		target->draw(text);
	}
