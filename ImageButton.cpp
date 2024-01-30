#include "stdafx.h"
#include "ImageButton.h"

	ImageButton::ImageButton(float x, float y, float width, float height, short text_size, sf::Font* font_
		, string text_, TextureManager* t_manager, int index, string name_, bool outline, int id_)
		: name(name_){
		id = id_;
		position = Vector2f(x, y);

		shape.setPosition(position);
		shape.setSize(sf::Vector2f(width, height));
		if (outline) {
			shape.setOutlineThickness(3.f);
			shape.setOutlineColor(Color::Black);
		}
		btn_image = new Sprite();
		btn_image->setTexture(t_manager->getTexture(index, name));
		float img_max_height = (shape.getSize().y * 80) / 100;
		btn_image->setScale(img_max_height/btn_image->getLocalBounds().height, img_max_height / btn_image->getLocalBounds().height);
		
		font = font_;
		text.setFont(*font);
		text.setString(text_);
		text.setFillColor(btn_idle_color);
		text.setCharacterSize(text_size);
		text.setOutlineThickness(3.f);
		text.setOutlineColor(sf::Color(0, 0, 0, 0));
		FloatRect ir = btn_image->getGlobalBounds();
		if (text.getGlobalBounds().width == 0) {
			btn_image->setPosition(
				shape.getPosition().x - shape.getOutlineThickness() + (width - btn_image->getGlobalBounds().width) / 2,
				shape.getPosition().y - shape.getOutlineThickness() + (height - img_max_height) / 2
			);
		}
		else {
			btn_image->setPosition(
				shape.getPosition().x - shape.getOutlineThickness() + (shape.getGlobalBounds().width - text.getLocalBounds().width - btn_image->getGlobalBounds().width - btn_image->getGlobalBounds().width / 2) / 2,
				shape.getPosition().y - shape.getOutlineThickness() + (shape.getGlobalBounds().height - btn_image->getGlobalBounds().height) / 2
			);
		}
		
		text.setPosition(
			btn_image->getPosition().x - shape.getOutlineThickness() + btn_image->getGlobalBounds().width + btn_image->getGlobalBounds().width / 2,
			shape.getPosition().y - shape.getOutlineThickness() - text.getLocalBounds().top + (shape.getGlobalBounds().height - text.getLocalBounds().height) / 2
		);
		
		shape.setFillColor(shp_idle_color);
	}
	
	void ImageButton::setPosition(Vector2f new_position){
		position = new_position;
		shape.setPosition(position);
		if (text.getGlobalBounds().width == 0) {
			btn_image->setPosition(
				shape.getPosition().x - shape.getOutlineThickness() - text.getLocalBounds().left + (shape.getGlobalBounds().width - text.getLocalBounds().width - btn_image->getGlobalBounds().width - (text.getLocalBounds().width == 0 ? 0 : btn_image->getGlobalBounds().width / 2)) / 2,
				shape.getPosition().y - shape.getOutlineThickness() - text.getLocalBounds().top + (shape.getGlobalBounds().height - ((text.getLocalBounds().height < btn_image->getGlobalBounds().height) ? btn_image->getGlobalBounds().height : text.getLocalBounds().height)) / 2
			);
		}
		else {
			btn_image->setPosition(
				shape.getPosition().x - shape.getOutlineThickness() + (shape.getGlobalBounds().width - text.getLocalBounds().width - btn_image->getGlobalBounds().width - btn_image->getGlobalBounds().width / 2) / 2,
				shape.getPosition().y - shape.getOutlineThickness() + (shape.getGlobalBounds().height - btn_image->getGlobalBounds().height) / 2
			);
		}
		text.setPosition(
			btn_image->getPosition().x - shape.getOutlineThickness() + btn_image->getGlobalBounds().width + btn_image->getGlobalBounds().width / 2,
			shape.getPosition().y - shape.getOutlineThickness() - text.getLocalBounds().top + (shape.getGlobalBounds().height - text.getLocalBounds().height) / 2
		);
	}
	
	void ImageButton::updatePosition(FloatRect view_cords){
		shape.setPosition(
			view_cords.left - view_cords.width / 2 + position.x,
			view_cords.top - view_cords.height / 2 + position.y
		);
		if (text.getGlobalBounds().width == 0) {
			btn_image->setPosition(
				shape.getPosition().x - shape.getOutlineThickness() - text.getLocalBounds().left + (shape.getGlobalBounds().width - text.getLocalBounds().width - btn_image->getGlobalBounds().width - (text.getLocalBounds().width == 0 ? 0 : btn_image->getGlobalBounds().width / 2)) / 2,
				shape.getPosition().y - shape.getOutlineThickness() - text.getLocalBounds().top + (shape.getGlobalBounds().height - ((text.getLocalBounds().height < btn_image->getGlobalBounds().height) ? btn_image->getGlobalBounds().height : text.getLocalBounds().height)) / 2
			);
		}
		else {
			btn_image->setPosition(
				shape.getPosition().x - shape.getOutlineThickness() + (shape.getGlobalBounds().width - text.getLocalBounds().width - btn_image->getGlobalBounds().width - btn_image->getGlobalBounds().width / 2) / 2,
				shape.getPosition().y - shape.getOutlineThickness() + (shape.getGlobalBounds().height - btn_image->getGlobalBounds().height) / 2
			);
		}
		text.setPosition(
			btn_image->getPosition().x - shape.getOutlineThickness() + btn_image->getGlobalBounds().width + btn_image->getGlobalBounds().width / 2,
			shape.getPosition().y - shape.getOutlineThickness() - text.getLocalBounds().top + (shape.getGlobalBounds().height - text.getLocalBounds().height) / 2
		);
	}
	
	void ImageButton::render(sf::RenderTarget* target){
		target->draw(shape);
		target->draw(*btn_image);
		target->draw(text);
	}
