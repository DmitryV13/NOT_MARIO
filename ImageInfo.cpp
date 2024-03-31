#include "stdafx.h"
#include "ImageInfo.h"

	ImageInfo::ImageInfo(){
		ii_type = INTERFACE_ITEM_TYPE::IMAGE_INFO;
		id = GlobalProcessData::getUnicId();
		shape.setFillColor(Color(0, 0, 0, 0));
	}

	ImageInfo::ImageInfo(float x, float y, string text_, int text_size,
		TextureManager* t_manager, int index, string name){
		ii_type = INTERFACE_ITEM_TYPE::IMAGE_INFO;
		id = GlobalProcessData::getUnicId();

		shape.setFillColor(Color(0, 0, 0, 0));
		position.x = x;
		position.y = y;
		src_img.setTexture(t_manager->getTexture(index, name));

		shape.setPosition(position);
		text.setFont(*GlobalProcessData::getFont());
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
			position.x + src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 - text.getLocalBounds().left,
			position.y + text.getLocalBounds().height / 2 - text.getLocalBounds().top
		);
	}

	ImageInfo::ImageInfo(float x, float y, int text_, int text_size, TextureManager* t_manager, 
		int index, string name){
		ii_type = INTERFACE_ITEM_TYPE::IMAGE_INFO;
		id = GlobalProcessData::getUnicId();

		shape.setFillColor(Color(0, 0, 0, 0));
		position.x = x;
		position.y = y;
		src_img.setTexture(t_manager->getTexture(index, name));

		shape.setPosition(position);
		text.setFont(*GlobalProcessData::getFont());
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
			position.x + src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 - text.getLocalBounds().left,
			position.y + text.getLocalBounds().height / 2 - text.getLocalBounds().top
		);
	}
	
	FloatRect ImageInfo::getLocalBounds(){
		return shape.getLocalBounds();
	}
	
	FloatRect ImageInfo::getGlobalBounds(){
		return shape.getGlobalBounds();
	}
	
	void ImageInfo::setPosition(Vector2f new_position){
		position = new_position;
		shape.setPosition(position);
		src_img.setPosition(position);

		text.setPosition(
			position.x + src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 - text.getLocalBounds().left,
			position.y + text.getLocalBounds().height / 2 - text.getLocalBounds().top
		);
	}
	
	void ImageInfo::setPositionX(float x){
		setPosition(Vector2f(x + shape.getOutlineThickness(), position.y));
	}
	
	void ImageInfo::setPositionY(float y){
		setPosition(Vector2f(position.x, y + shape.getOutlineThickness()));
	}

	void ImageInfo::setText(float text_){
		text.setString(std::to_string(static_cast<int>(text_)));
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

	void ImageInfo::setBackgroundColor(Color color){
		shape.setFillColor(color);
	}

	void ImageInfo::changePosition(float offset_x, float offset_y){
		setPosition(Vector2f(position.x + offset_x, position.y + offset_y));
	}
	
	void ImageInfo::update(){
		FloatRect view_cords = GlobalProcessData::getViewCords();

		shape.setPosition(Vector2f(
			position.x + view_cords.left - view_cords.width / 2,
			position.y + view_cords.top - view_cords.height / 2)
		);
		src_img.setPosition(Vector2f(
			position.x + view_cords.left - view_cords.width / 2,
			position.y + view_cords.top - view_cords.height / 2)
		);
		text.setPosition(
			position.x + src_img.getGlobalBounds().width + src_img.getGlobalBounds().height / 2 - text.getLocalBounds().left,
			position.y + text.getLocalBounds().height / 2 - text.getLocalBounds().top
		);
	}
	
	void ImageInfo::render(){
		RenderTarget* target = GlobalProcessData::getWindow();

		target->draw(src_img);
		target->draw(text);
	}
