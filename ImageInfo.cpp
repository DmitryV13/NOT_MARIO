#include "stdafx.h"
#include "ImageInfo.h"

	ImageInfo::ImageInfo(){
		ii_type = INTERFACE_ITEM_TYPE::IMAGE_INFO;
		shape.setFillColor(Color(0, 0, 0, 0));
	}

	ImageInfo::ImageInfo(float x, float y, string text_, int text_size, Font* font,
		TextureManager* t_manager, int index, string name){
		ii_type = INTERFACE_ITEM_TYPE::IMAGE_INFO;
		shape.setFillColor(Color(0, 0, 0, 0));
		src_img.setTexture(t_manager->getTexture(index, name));

		shape.setPosition(x, y);
		text.setFont(*font);
		text.setString(text_);
		text.setFillColor(Color::White);
		text.setCharacterSize(text_size);
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
			shape.getPosition().x + src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 - text.getLocalBounds().left,
			shape.getPosition().y + text.getLocalBounds().height / 2 - text.getLocalBounds().top
		);

		shape.setFillColor(Color(0, 0, 0, 0));
	}

	ImageInfo::ImageInfo(float x, float y, int text_, int text_size, Font* font, TextureManager* t_manager, int index, string name){
		ii_type = INTERFACE_ITEM_TYPE::IMAGE_INFO;
		shape.setFillColor(Color(0, 0, 0, 0));
		src_img.setTexture(t_manager->getTexture(index, name));

		shape.setPosition(x, y);
		text.setFont(*font);
		text.setString(std::to_string(text_));
		text.setFillColor(Color::White);
		text.setCharacterSize(text_size);
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
			shape.getPosition().x + src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 - text.getLocalBounds().left,
			shape.getPosition().y + text.getLocalBounds().height / 2 - text.getLocalBounds().top
		);

		shape.setFillColor(Color(0, 0, 0, 0));
	}
	
	FloatRect ImageInfo::getLocalBounds(){
		return shape.getLocalBounds();
	}
	
	FloatRect ImageInfo::getGlobalBounds(){
		return shape.getGlobalBounds();
	}
	
	void ImageInfo::setPosition(Vector2f new_position){
		shape.setPosition(new_position);
		src_img.setPosition(shape.getPosition());

		text.setPosition(
			shape.getPosition().x + src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 - text.getLocalBounds().left,
			shape.getPosition().y + text.getLocalBounds().height / 2 - text.getLocalBounds().top
		);
	}
	
	void ImageInfo::setPositionX(float x){
		setPosition(Vector2f(x + shape.getOutlineThickness(), shape.getPosition().y));
	}
	
	void ImageInfo::setPositionY(float y){
		setPosition(Vector2f(shape.getPosition().x, y + shape.getOutlineThickness()));
	}

	void ImageInfo::setText(float text_){
		text.setString(std::to_string(static_cast<int>(text_)));
		shape.setSize(Vector2f(
			src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 + text.getGlobalBounds().width,
			text.getGlobalBounds().height * 2)
		);

		src_img.setPosition(shape.getPosition());

		text.setPosition(
			shape.getPosition().x + src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 - text.getLocalBounds().left,
			shape.getPosition().y + text.getLocalBounds().height / 2 - text.getLocalBounds().top
		);
	}

	void ImageInfo::setBackgroundColor(Color color){
		shape.setFillColor(color);
	}
	
	void ImageInfo::changePosition(float offset_x, float offset_y){
		setPosition(Vector2f(shape.getPosition().x + offset_x, shape.getPosition().y + offset_y));
	}
	
	void ImageInfo::update(Vector2f mouse_pos, FloatRect view_cords){
		setPosition
		(Vector2f(shape.getPosition().x + view_cords.left - view_cords.width / 2,
			shape.getPosition().y + view_cords.top - view_cords.height / 2)
		);
	}
	
	void ImageInfo::render(sf::RenderTarget* target){
		target->draw(src_img);
		target->draw(text);
	}
