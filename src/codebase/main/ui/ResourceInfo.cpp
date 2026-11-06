#include "stdafx.h"
#include "ui/ResourceInfo.h"

	ResourceInfo::ResourceInfo(){
	}

	ResourceInfo::ResourceInfo(float x, float y, Font* font, int text_size, bool image_){
		image = image_;
		position.x = x;
		position.y = y;
		shape.setPosition(position);
		text.setFont(*font);
		text.setCharacterSize(text_size);
	}
	
	ResourceInfo::ResourceInfo(float x, float y, int text_size, Font* font
		, TextureManager* t_manager, Warehouse* w_object, string name, bool image_)
		: image(image_) {
		position.x = x;
		position.y = y;
		resource = w_object->getWarehouseItem(name)->getInfo().first;
		src_img.setTexture(t_manager->getTexture(w_object->getWarehouseItem(name)->getTMInfo().first, name));

		shape.setPosition(position);
		max = w_object->getWarehouseItem(name)->getInfo().second == 0 ? "" : "/" + std::to_string(w_object->getWarehouseItem(name)->getInfo().second);
		text.setFont(*font);
		text.setString(std::to_string(*resource) + max);
		text.setFillColor(Color::White);
		text.setCharacterSize(text_size);
		//resource_name.setOutlineThickness(3.f);
		//resource_name.setOutlineColor(sf::Color(0, 0, 0, 0));
		src_img.setScale(sf::Vector2f((text.getGlobalBounds().size.y * 2) / src_img.getGlobalBounds().size.y, (text.getGlobalBounds().size.y * 2) / src_img.getGlobalBounds().size.y));

		shape.setSize(Vector2f(
			src_img.getGlobalBounds().size.x + src_img.getGlobalBounds().size.y / 2 + text.getGlobalBounds().size.x,
			text.getGlobalBounds().size.y * 2)
		);

		src_img.setPosition(shape.getPosition());

		text.setPosition(sf::Vector2f(position.x + src_img.getGlobalBounds().size.x + src_img.getGlobalBounds().size.y / 2 - text.getLocalBounds().position.x, position.y + text.getLocalBounds().size.y / 2 - text.getLocalBounds().position.y));

		shape.setFillColor(Color(0, 0, 0, 0));
	}

	ResourceInfo::ResourceInfo(float x, float y, int* resource_, int max_v, int text_size, Font* font
		, TextureManager* t_manager, int index, string name, bool self_align_)
		: resource(resource_), image(self_align_){
		src_img.setTexture(t_manager->getTexture(index, name));
		position.x = x;
		position.y = y;
		shape.setPosition(position);
		max = max_v==0?"": "/" + std::to_string(max_v);
		text.setFont(*font);
		text.setString(std::to_string(*resource) + max);
		text.setFillColor(Color::White);
		text.setCharacterSize(text_size);
		//resource_name.setOutlineThickness(3.f);
		//resource_name.setOutlineColor(sf::Color(0, 0, 0, 0));
		src_img.setScale(sf::Vector2f((text.getGlobalBounds().size.y * 2) / src_img.getGlobalBounds().size.y, (text.getGlobalBounds().size.y * 2) / src_img.getGlobalBounds().size.y));

		shape.setSize(Vector2f(
			src_img.getGlobalBounds().size.x + src_img.getGlobalBounds().size.y/2 + text.getGlobalBounds().size.x,
			text.getGlobalBounds().size.y * 2)
		);

		src_img.setPosition(shape.getPosition());

		text.setPosition(sf::Vector2f(position.x + src_img.getGlobalBounds().size.x + src_img.getGlobalBounds().size.y / 2 - text.getLocalBounds().position.x, position.y + text.getLocalBounds().size.y/2 - text.getLocalBounds().position.y));

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
				text.getGlobalBounds().size.x * 2,
				text.getGlobalBounds().size.y * 2)
			);

			text.setPosition(sf::Vector2f(position.x - text.getLocalBounds().position.x + text.getGlobalBounds().size.x/2, position.y - text.getLocalBounds().position.y + text.getGlobalBounds().size.y/2));
		}
		else {
			src_img.setTexture(t_manager->getTexture(w_object->getWarehouseItem(name)->getTMInfo().first, name));
			src_img.setScale(sf::Vector2f((text.getGlobalBounds().size.y * 2) / src_img.getGlobalBounds().size.y, (text.getGlobalBounds().size.y * 2) / src_img.getGlobalBounds().size.y));

			shape.setSize(Vector2f(
				src_img.getGlobalBounds().size.x + src_img.getGlobalBounds().size.y / 2 + text.getGlobalBounds().size.x,
				text.getGlobalBounds().size.y * 2)
			);

			src_img.setPosition(shape.getPosition());

			text.setPosition(sf::Vector2f(position.x + src_img.getGlobalBounds().size.x + src_img.getGlobalBounds().size.y / 2 - text.getLocalBounds().position.x, position.y + text.getLocalBounds().size.y / 2 - text.getLocalBounds().position.y));
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
				text.getGlobalBounds().size.x * 2,
				text.getGlobalBounds().size.y * 2)
			);

			text.setPosition(sf::Vector2f(position.x - text.getLocalBounds().position.x + text.getGlobalBounds().size.x / 2, position.y - text.getLocalBounds().position.y + text.getGlobalBounds().size.y / 2));
		}
		else {
			src_img.setTexture(t_manager->getTexture(w_item->getTMInfo().first, w_item->getTMInfo().second));
			src_img.setScale(sf::Vector2f((text.getGlobalBounds().size.y * 2) / src_img.getGlobalBounds().size.y, (text.getGlobalBounds().size.y * 2) / src_img.getGlobalBounds().size.y));

			shape.setSize(Vector2f(
				src_img.getGlobalBounds().size.x + src_img.getGlobalBounds().size.y / 2 + text.getGlobalBounds().size.x,
				text.getGlobalBounds().size.y * 2)
			);

			src_img.setPosition(position);

			text.setPosition(sf::Vector2f(position.x + src_img.getGlobalBounds().size.x + src_img.getGlobalBounds().size.y / 2 - text.getLocalBounds().position.x, position.y + text.getLocalBounds().size.y / 2 - text.getLocalBounds().position.y));
		}


		shape.setFillColor(Color(0, 0, 0, 0));
	}

	void ResourceInfo::update(Vector2f mouse_pos, FloatRect view_cords){
		shape.setPosition(Vector2f(
			position.x + view_cords.position.x - view_cords.size.x / 2,
			position.y + view_cords.position.y - view_cords.size.y / 2)
		);

		if (resource) {
			text.setString(prev + std::to_string(*resource) + max);
			if (image) {
				shape.setSize(Vector2f(
					src_img.getGlobalBounds().size.x + src_img.getGlobalBounds().size.y / 2 + text.getGlobalBounds().size.x,
					text.getGlobalBounds().size.y * 2)
				);

				src_img.setPosition(Vector2f(
					position.x + view_cords.position.x - view_cords.size.x / 2,
					position.y + view_cords.position.y - view_cords.size.y / 2)
				);

				text.setPosition(sf::Vector2f(view_cords.position.x - view_cords.size.x / 2 + position.x + src_img.getGlobalBounds().size.x + src_img.getGlobalBounds().size.y / 2 - text.getLocalBounds().position.x, view_cords.position.y - view_cords.size.y / 2 + position.y + text.getLocalBounds().size.y / 2 - text.getLocalBounds().position.y));
			}
			else {
				shape.setSize(Vector2f(
					text.getGlobalBounds().size.x * 2,
					text.getGlobalBounds().size.y * 2)
				);
			
				text.setPosition(sf::Vector2f(view_cords.position.x - view_cords.size.x / 2 + position.x - text.getLocalBounds().position.x + text.getGlobalBounds().size.x / 2, view_cords.position.y - view_cords.size.y / 2 + position.y - text.getLocalBounds().position.y + text.getGlobalBounds().size.y / 2));
			}
		}
	}

