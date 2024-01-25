#include "stdafx.h"
#include "InventoryItem.h"

	InventoryItem::InventoryItem(float x, float y, float width_, float height_, int text_size_, Font* font)
		:position(Vector2f(x, y)), width(width_), height(height_), text_size(text_size_){
		image = new BasicImage(x, y);
		r_info = new ResourceInfo(x, y, font, text_size_, true);
	}

	void InventoryItem::addItemInfo(TextureManager* t_manager, Warehouse* w_object, string name){
		image->addInfo(t_manager, w_object, name);
		r_info->addInfo(t_manager, w_object, name);
	}

	FloatRect InventoryItem::getLocalBounds(){
		return FloatRect(position, Vector2f(width, height));
	}

	FloatRect InventoryItem::getGlobalBounds(){
		return FloatRect(position, Vector2f(width, height));
	}

	void InventoryItem::setPositionX(float x){
	}

	void InventoryItem::setPositionY(float y){
	}

	void InventoryItem::changePosition(float offset_x, float offset_y){
	}

	void InventoryItem::update(Vector2f mouse_pos, FloatRect view_cords){
		image->update(mouse_pos, view_cords);
		r_info->update(mouse_pos, view_cords);
		//text.setPosition();
	}

	void InventoryItem::render(RenderTarget* target){
		image->render(target);
		r_info->render(target);
		target->draw(text);
	}
