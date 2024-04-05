#include "stdafx.h"
#include "BasicImage.h"

	BasicImage::BasicImage(){
		ii_type = INTERFACE_ITEM_TYPE::BASIC_IMAGE;
		id = GlobalProcessData::getUnicId();
	}
	
	BasicImage::BasicImage(float x, float y){
		ii_type = INTERFACE_ITEM_TYPE::BASIC_IMAGE;
		id = GlobalProcessData::getUnicId();

		position.x = x;
		position.y = y;
		shape.setPosition(position);
		shape.setFillColor(Color(0, 0, 0, 0));
	}

	BasicImage::BasicImage(TextureManager* t_manager, Warehouse* w_object, string name){
		ii_type = INTERFACE_ITEM_TYPE::BASIC_IMAGE;
		id = GlobalProcessData::getUnicId();

		image.setTexture(t_manager->getTexture(w_object->getWarehouseItem(name)->getTMInfo().first, name));
		image.setTextureRect(w_object->getWarehouseItem(name)->getSpriteInfo().first);
		shape.setFillColor(Color(0, 0, 0, 0));
		shape.setSize(Vector2f(image.getTextureRect().width, image.getTextureRect().height));
	}

	BasicImage::BasicImage(float width, float height, TextureManager* t_manager, Warehouse* w_object, string name){
		ii_type = INTERFACE_ITEM_TYPE::BASIC_IMAGE;
		id = GlobalProcessData::getUnicId();

		shape.setFillColor(Color(0, 0, 0, 0));
		shape.setSize(Vector2f(width, height));

		image.setTexture(t_manager->getTexture(w_object->getWarehouseItem(name)->getTMInfo().first, name));
		image.setTextureRect(w_object->getWarehouseItem(name)->getSpriteInfo().first);
		float img_max_height = shape.getSize().y;
		float img_max_width = shape.getSize().x;
		float max_param = (img_max_height / image.getLocalBounds().height) < (img_max_width / image.getLocalBounds().width) ? img_max_height : img_max_width;
		float basic_param = (img_max_height / image.getLocalBounds().height) < (img_max_width / image.getLocalBounds().width) ? image.getLocalBounds().height : image.getLocalBounds().width;
		image.setScale(max_param / basic_param, max_param / basic_param);
	}
	
	BasicImage::BasicImage(TextureManager* t_manager, int index, string name, IntRect frame){
		ii_type = INTERFACE_ITEM_TYPE::BASIC_IMAGE;
		id = GlobalProcessData::getUnicId();

		image.setTexture(t_manager->getTexture(index, name));
		image.setTextureRect(frame);
		shape.setFillColor(Color(0, 0, 0, 0));
		shape.setSize(Vector2f(image.getTextureRect().width, image.getTextureRect().height));
	}

	BasicImage::BasicImage(float width, float height, TextureManager* t_manager, int index, string name, 
		IntRect frame){
		ii_type = INTERFACE_ITEM_TYPE::BASIC_IMAGE;
		id = GlobalProcessData::getUnicId();

		shape.setFillColor(Color(0, 0, 0, 0));
		shape.setSize(Vector2f(width, height));

		image.setTexture(t_manager->getTexture(index, name));
		image.setTextureRect(frame);
		float img_max_height = shape.getSize().y;
		float img_max_width = shape.getSize().x;
		float max_param = (img_max_height / image.getLocalBounds().height) < (img_max_width / image.getLocalBounds().width) ? img_max_height : img_max_width;
		float basic_param = (img_max_height / image.getLocalBounds().height) < (img_max_width / image.getLocalBounds().width) ? image.getLocalBounds().height : image.getLocalBounds().width;
		image.setScale(max_param / basic_param, max_param / basic_param);
	}

	BasicImage::~BasicImage(){
	}

	void BasicImage::addInfo(TextureManager* t_manager, Warehouse* w_object, string name){
		image.setTexture(t_manager->getTexture(w_object->getWarehouseItem(name)->getTMInfo().first, name));
		image.setTextureRect(w_object->getWarehouseItem(name)->getSpriteInfo().first);
		shape.setSize(Vector2f(image.getTextureRect().width, image.getTextureRect().height));
	}

	void BasicImage::addInfo(TextureManager* t_manager, WarehouseItem* w_item){
		image.setTexture(t_manager->getTexture(w_item->getTMInfo().first, w_item->getTMInfo().second));
		image.setTextureRect(w_item->getSpriteInfo().first);
		shape.setSize(Vector2f(image.getTextureRect().width, image.getTextureRect().height));
	}
	
	FloatRect BasicImage::getLocalBounds(){
		return image.getLocalBounds();
	}
	
	FloatRect BasicImage::getGlobalBounds(){
		return image.getGlobalBounds();
	}
	
	void BasicImage::changePosition(float offset_x, float offset_y){
		position.x += offset_x;
		position.y += offset_y;
	}

	void BasicImage::setPositionX(float x){
		float offset = x - position.x;
		changePosition(offset, 0);
	}

	void BasicImage::setPositionY(float y){
		float offset = y - position.y;
		changePosition(0, offset);
	}

	void BasicImage::setPosition(float x, float y){
		position.x = x;
		position.y = y;
		image.setPosition(position);
		shape.setPosition(position);
	}
	
	void BasicImage::setScale(float scale_){
		scale = scale_;
		image.setScale(scale, scale);
		shape.setScale(scale, scale);
	}

	void BasicImage::setBColor(Color color){
		shape.setFillColor(color);
	}
	
	void BasicImage::update(){
		FloatRect view_cords = GlobalProcessData::getViewCords();

		image.setPosition(
			position.x + view_cords.left - view_cords.width / 2,
			position.y + view_cords.top - view_cords.height / 2
		);
		shape.setPosition(
			position.x + view_cords.left - view_cords.width / 2,
			position.y + view_cords.top - view_cords.height / 2
		);
	}
	
	void BasicImage::render(){
		RenderTarget* target = GlobalProcessData::getWindow();

		target->draw(shape);
		target->draw(image);
	}
