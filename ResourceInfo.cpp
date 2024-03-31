#include "stdafx.h"
#include "ResourceInfo.h"

	ResourceInfo::ResourceInfo(){
		ii_type = INTERFACE_ITEM_TYPE::RESOURCE_INFO;
	}

	ResourceInfo::ResourceInfo(float x, float y, int text_size, bool image_){
		ii_type = INTERFACE_ITEM_TYPE::RESOURCE_INFO;

		image = image_;
		position.x = x;
		position.y = y;
		shape.setPosition(position);
		text.setFont(*GlobalProcessData::getFont());
		text.setCharacterSize(text_size);
	}
	
	ResourceInfo::ResourceInfo(float x, float y, int text_size
		, TextureManager* t_manager, Warehouse* w_object, string name, bool image_)
		: image(image_) {
		ii_type = INTERFACE_ITEM_TYPE::RESOURCE_INFO;

		position.x = x;
		position.y = y;
		resource = w_object->getWarehouseItem(name)->getInfo().first;
		src_img.setTexture(t_manager->getTexture(w_object->getWarehouseItem(name)->getTMInfo().first, name));

		shape.setPosition(position);
		max = w_object->getWarehouseItem(name)->getInfo().second == 0 ? "" : "/" + std::to_string(w_object->getWarehouseItem(name)->getInfo().second);
		text.setFont(*GlobalProcessData::getFont());
		text.setString(std::to_string(*resource) + max);
		text.setFillColor(Color::White);
		text.setCharacterSize(text_size);
		//resource_name.setOutlineThickness(3.f);
		//resource_name.setOutlineColor(sf::Color(0, 0, 0, 0));
		src_img.setScale(
			(text.getGlobalBounds().height * 2) / src_img.getGlobalBounds().height,
			(text.getGlobalBounds().height * 2) / src_img.getGlobalBounds().height
		);

		shape.setSize(Vector2f(
			src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 + text.getGlobalBounds().width,
			text.getGlobalBounds().height * 2)
		);

		src_img.setPosition(shape.getPosition());

		text.setPosition(
			position.x + src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 - text.getLocalBounds().left,
			position.y + text.getLocalBounds().height / 2 - text.getLocalBounds().top
		);

		shape.setFillColor(Color(0, 0, 0, 0));
	}

	ResourceInfo::ResourceInfo(float x, float y, int* resource_, int max_v, int text_size
		, TextureManager* t_manager, int index, string name, bool self_align_)
		: resource(resource_), image(self_align_){
		ii_type = INTERFACE_ITEM_TYPE::RESOURCE_INFO;

		src_img.setTexture(t_manager->getTexture(index, name));
		position.x = x;
		position.y = y;
		shape.setPosition(position);
		max = max_v==0?"": "/" + std::to_string(max_v);
		text.setFont(*GlobalProcessData::getFont());
		text.setString(std::to_string(*resource) + max);
		text.setFillColor(Color::White);
		text.setCharacterSize(text_size);
		//resource_name.setOutlineThickness(3.f);
		//resource_name.setOutlineColor(sf::Color(0, 0, 0, 0));
		src_img.setScale(
			(text.getGlobalBounds().height * 2) / src_img.getGlobalBounds().height,
			(text.getGlobalBounds().height * 2) / src_img.getGlobalBounds().height
		);

		shape.setSize(Vector2f(
			src_img.getGlobalBounds().width + src_img.getGlobalBounds().height/2 + text.getGlobalBounds().width,
			text.getGlobalBounds().height * 2)
		);

		src_img.setPosition(shape.getPosition());

		text.setPosition(
			position.x + src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 - text.getLocalBounds().left,
			position.y + text.getLocalBounds().height/2 - text.getLocalBounds().top
		);

		shape.setFillColor(Color(0,0,0,0));
	}

	void ResourceInfo::addInfo(TextureManager* t_manager, Warehouse* w_object, string name, bool x){
		resource = w_object->getWarehouseItem(name)->getInfo().first;
		if (x) {
			prev = "x";
		}
		else {
			prev = "";
		}
		max = w_object->getWarehouseItem(name)->getInfo().second == 0 ? "" : "/" + std::to_string(w_object->getWarehouseItem(name)->getInfo().second);
		text.setString(prev + std::to_string(*resource) + max);
		text.setFillColor(Color::White);

		if (!image) {
			shape.setSize(Vector2f(
				text.getGlobalBounds().width * 2,
				text.getGlobalBounds().height * 2)
			);

			text.setPosition(
				position.x - text.getLocalBounds().left + text.getGlobalBounds().width/2,
				position.y - text.getLocalBounds().top + text.getGlobalBounds().height/2
			);
		}
		else {
			src_img.setTexture(t_manager->getTexture(w_object->getWarehouseItem(name)->getTMInfo().first, name));
			src_img.setScale(
				(text.getGlobalBounds().height * 2) / src_img.getGlobalBounds().height,
				(text.getGlobalBounds().height * 2) / src_img.getGlobalBounds().height
			);

			shape.setSize(Vector2f(
				src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 + text.getGlobalBounds().width,
				text.getGlobalBounds().height * 2)
			);

			src_img.setPosition(shape.getPosition());

			text.setPosition(
				position.x + src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 - text.getLocalBounds().left,
				position.y + text.getLocalBounds().height / 2 - text.getLocalBounds().top
			);
		}


		shape.setFillColor(Color(0, 0, 0, 0));
	}

	void ResourceInfo::addInfo(TextureManager* t_manager, WarehouseItem* w_item, bool x){
		resource = w_item->getInfo().first;
		if (x) {
			prev = "x";
		}
		else {
			prev = "";
		}
		string h= prev + std::to_string(*resource) + max;
		max = w_item->getInfo().second == 0 ? "" : "/" + std::to_string(w_item->getInfo().second);
		text.setString(prev + std::to_string(*resource) + max);
		text.setFillColor(Color::White);

		if (!image) {
			shape.setSize(Vector2f(
				text.getGlobalBounds().width * 2,
				text.getGlobalBounds().height * 2)
			);

			text.setPosition(
				position.x - text.getLocalBounds().left + text.getGlobalBounds().width / 2,
				position.y - text.getLocalBounds().top + text.getGlobalBounds().height / 2
			);
		}
		else {
			src_img.setTexture(t_manager->getTexture(w_item->getTMInfo().first, w_item->getTMInfo().second));
			src_img.setScale(
				(text.getGlobalBounds().height * 2) / src_img.getGlobalBounds().height,
				(text.getGlobalBounds().height * 2) / src_img.getGlobalBounds().height
			);

			shape.setSize(Vector2f(
				src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 + text.getGlobalBounds().width,
				text.getGlobalBounds().height * 2)
			);

			src_img.setPosition(position);

			text.setPosition(
				position.x + src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 - text.getLocalBounds().left,
				position.y + text.getLocalBounds().height / 2 - text.getLocalBounds().top
			);
		}


		shape.setFillColor(Color(0, 0, 0, 0));
	}

	void ResourceInfo::update(){
		Vector2f mouse_pos = GlobalProcessData::getMousePos();
		FloatRect view_cords = GlobalProcessData::getViewCords();

		shape.setPosition(Vector2f(
			position.x + view_cords.left - view_cords.width / 2,
			position.y + view_cords.top - view_cords.height / 2)
		);

		if (resource) {
			text.setString(prev + std::to_string(*resource) + max);
			if (image) {
				shape.setSize(Vector2f(
					src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 + text.getGlobalBounds().width,
					text.getGlobalBounds().height * 2)
				);

				src_img.setPosition(Vector2f(
					position.x + view_cords.left - view_cords.width / 2,
					position.y + view_cords.top - view_cords.height / 2)
				);

				text.setPosition(
					view_cords.left - view_cords.width / 2 + position.x + src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 - text.getLocalBounds().left,
					view_cords.top - view_cords.height / 2 + position.y + text.getLocalBounds().height / 2 - text.getLocalBounds().top
				);
			}
			else {
				shape.setSize(Vector2f(
					text.getGlobalBounds().width * 2,
					text.getGlobalBounds().height * 2)
				);
			
				text.setPosition(
					view_cords.left - view_cords.width / 2 + position.x - text.getLocalBounds().left + text.getGlobalBounds().width / 2,
					view_cords.top - view_cords.height / 2 + position.y - text.getLocalBounds().top + text.getGlobalBounds().height / 2
				);
			}
		}
	}

