#include "stdafx.h"
#include "BasicImage.h"

	BasicImage::BasicImage(){
	}
	
	BasicImage::BasicImage(float x, float y){
		position.x = x;
		position.y = y;
		shape.setPosition(position);
		shape.setFillColor(Color(0, 0, 0, 0));
	}

	BasicImage::BasicImage(TextureManager* t_manager, Warehouse* w_object, string name){
		image.setTexture(t_manager->getTexture(w_object->getWarehouseItem(name)->getTMInfo().first, name));
		image.setTextureRect(w_object->getWarehouseItem(name)->getSpriteInfo().first);
		shape.setFillColor(Color(0, 0, 0, 0));
		shape.setSize(Vector2f(image.getTextureRect().width, image.getTextureRect().height));
	}
	
	BasicImage::BasicImage(TextureManager* t_manager, int index, string name, IntRect frame){
		image.setTexture(t_manager->getTexture(index, name));
		image.setTextureRect(frame);
		shape.setFillColor(Color(0, 0, 0, 0));
		shape.setSize(Vector2f(image.getTextureRect().width, image.getTextureRect().height));
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
