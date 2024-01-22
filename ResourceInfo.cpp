#include "stdafx.h"
#include "ResourceInfo.h"

	ResourceInfo::ResourceInfo(float x, float y, int* resource_, int max_v, int text_size, Font* font
		, TextureManager* t_manager, int index, string name): resource(resource_){
		src_img.setTexture(t_manager->getTexture(index, name));

		shape.setPosition(x, y);
		max = max_v==0?"": "/" + std::to_string(max_v);
		text.setFont(*font);
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
			shape.getPosition().x + src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 - text.getLocalBounds().left,
			shape.getPosition().y + text.getLocalBounds().height/2 - text.getLocalBounds().top
		);

		shape.setFillColor(Color(0,0,0,0));
	}

	void ResourceInfo::update(Vector2f mouse_pos, FloatRect view_cords){
		setPosition
		(Vector2f(shape.getPosition().x + view_cords.left - view_cords.width / 2,
			shape.getPosition().y + view_cords.top - view_cords.height / 2)
		);
		text.setString(std::to_string(*resource) + max);
	}

