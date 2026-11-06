#include "stdafx.h"
#include "ui/ImageButton.h"

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
		btn_image = new Sprite(Global::dummyTexture);
		btn_image->setTexture(t_manager->getTexture(index, name));
		float img_max_height = (shape.getSize().y * 80) / 100;
		btn_image->setScale(Vector2(img_max_height/btn_image->getLocalBounds().size.y, img_max_height / btn_image->getLocalBounds().size.y));
		
		font = font_;
		text.setFont(*font);
		text.setString(text_);
		text.setFillColor(btn_idle_color);
		text.setCharacterSize(text_size);
		text.setOutlineThickness(3.f);
		text.setOutlineColor(sf::Color(0, 0, 0, 0));
		FloatRect ir = btn_image->getGlobalBounds();
		if (text.getGlobalBounds().size.x == 0) {
			btn_image->setPosition(Vector2(
				shape.getPosition().x - shape.getOutlineThickness() + (width - btn_image->getGlobalBounds().size.x) / 2,
				shape.getPosition().y - shape.getOutlineThickness() + (height - img_max_height) / 2
			));
		}
		else {
			btn_image->setPosition(Vector2(
				shape.getPosition().x - shape.getOutlineThickness() + (shape.getGlobalBounds().size.x - text.getLocalBounds().size.x - btn_image->getGlobalBounds().size.x - btn_image->getGlobalBounds().size.x / 2) / 2,
				shape.getPosition().y - shape.getOutlineThickness() + (shape.getGlobalBounds().size.y - btn_image->getGlobalBounds().size.y) / 2
			));
		}
		
		text.setPosition(sf::Vector2f(btn_image->getPosition().x - shape.getOutlineThickness() + btn_image->getGlobalBounds().size.x + btn_image->getGlobalBounds().size.x / 2, shape.getPosition().y - shape.getOutlineThickness() - text.getLocalBounds().position.y + (shape.getGlobalBounds().size.y - text.getLocalBounds().size.y) / 2));
		
		shape.setFillColor(shp_idle_color);
	}
	
	void ImageButton::setPosition(Vector2f new_position){
		position = new_position;
		shape.setPosition(position);
		if (text.getGlobalBounds().size.x == 0) {
			btn_image->setPosition(Vector2(
				shape.getPosition().x - shape.getOutlineThickness() - text.getLocalBounds().position.x + (shape.getGlobalBounds().size.x - text.getLocalBounds().size.x - btn_image->getGlobalBounds().size.x - (text.getLocalBounds().size.x == 0 ? 0 : btn_image->getGlobalBounds().size.x / 2)) / 2,
				shape.getPosition().y - shape.getOutlineThickness() - text.getLocalBounds().position.y + (shape.getGlobalBounds().size.y - ((text.getLocalBounds().size.y < btn_image->getGlobalBounds().size.y) ? btn_image->getGlobalBounds().size.y : text.getLocalBounds().size.y)) / 2
			));
		}
		else {
			btn_image->setPosition(Vector2(
				shape.getPosition().x - shape.getOutlineThickness() + (shape.getGlobalBounds().size.x - text.getLocalBounds().size.x - btn_image->getGlobalBounds().size.x - btn_image->getGlobalBounds().size.x / 2) / 2,
				shape.getPosition().y - shape.getOutlineThickness() + (shape.getGlobalBounds().size.y - btn_image->getGlobalBounds().size.y) / 2
			));
		}
		text.setPosition(sf::Vector2f(btn_image->getPosition().x - shape.getOutlineThickness() + btn_image->getGlobalBounds().size.x + btn_image->getGlobalBounds().size.x / 2, shape.getPosition().y - shape.getOutlineThickness() - text.getLocalBounds().position.y + (shape.getGlobalBounds().size.y - text.getLocalBounds().size.y) / 2));
	}
	
	void ImageButton::updatePosition(FloatRect view_cords){
		shape.setPosition(sf::Vector2f(view_cords.position.x - view_cords.size.x / 2 + position.x, view_cords.position.y - view_cords.size.y / 2 + position.y));
		if (text.getGlobalBounds().size.x == 0) {
			btn_image->setPosition(Vector2(
				shape.getPosition().x - shape.getOutlineThickness() - text.getLocalBounds().position.x + (shape.getGlobalBounds().size.x - text.getLocalBounds().size.x - btn_image->getGlobalBounds().size.x - (text.getLocalBounds().size.x == 0 ? 0 : btn_image->getGlobalBounds().size.x / 2)) / 2,
				shape.getPosition().y - shape.getOutlineThickness() - text.getLocalBounds().position.y + (shape.getGlobalBounds().size.y - ((text.getLocalBounds().size.y < btn_image->getGlobalBounds().size.y) ? btn_image->getGlobalBounds().size.y : text.getLocalBounds().size.y)) / 2
			));
		}
		else {
			btn_image->setPosition(Vector2(
				shape.getPosition().x - shape.getOutlineThickness() + (shape.getGlobalBounds().size.x - text.getLocalBounds().size.x - btn_image->getGlobalBounds().size.x - btn_image->getGlobalBounds().size.x / 2) / 2,
				shape.getPosition().y - shape.getOutlineThickness() + (shape.getGlobalBounds().size.y - btn_image->getGlobalBounds().size.y) / 2
			));
		}
		text.setPosition(sf::Vector2f(btn_image->getPosition().x - shape.getOutlineThickness() + btn_image->getGlobalBounds().size.x + btn_image->getGlobalBounds().size.x / 2, shape.getPosition().y - shape.getOutlineThickness() - text.getLocalBounds().position.y + (shape.getGlobalBounds().size.y - text.getLocalBounds().size.y) / 2));
	}
	
	void ImageButton::render(sf::RenderTarget* target){
		target->draw(shape);
		target->draw(*btn_image);
		target->draw(text);
	}
