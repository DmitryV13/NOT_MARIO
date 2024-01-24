#include "stdafx.h"
#include "BasicImage.h"

	BasicImage::BasicImage(){
	}

	BasicImage::BasicImage(TextureManager* t_manager, Warehouse* w_object, string name){
		image.setTexture(t_manager->getTexture(w_object->getWarehouseItem(name)->getTMInfo().first, name));
		image.setTextureRect(w_object->getWarehouseItem(name)->getSpriteInfo().first);
	}
	
	BasicImage::BasicImage(TextureManager* t_manager, int index, string name, IntRect frame){
		image.setTexture(t_manager->getTexture(index, name));
		image.setTextureRect(frame);
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
	}
	
	void BasicImage::setScale(float scale_){
		scale = scale_;
		image.setScale(scale, scale);
	}
	
	void BasicImage::update(Vector2f mouse_pos, FloatRect view_cords){
		image.setPosition(
			position.x + view_cords.left - view_cords.width / 2,
			position.y + view_cords.top - view_cords.height / 2
		);
	}
	
	void BasicImage::render(RenderTarget* target){
		target->draw(image);
	}
