#include "stdafx.h"
#include "InterfaceItem.h"

	void InterfaceItem::render(sf::RenderTarget* target){
	}
	
	void InterfaceItem::update(Vector2f mouse_pos, FloatRect view_cords){
	}

	FloatRect InterfaceItem::getLocalBounds(){
		return FloatRect();
	}

	FloatRect InterfaceItem::getGlobalBounds(){
		return FloatRect();
	}

	short& InterfaceItem::getIIType(){
		return ii_type;
	}

	void InterfaceItem::setPositionX(float x){
	}

	void InterfaceItem::setPositionY(float y){
	}

	void InterfaceItem::changePosition(float offset_x, float offset_y){
	}

	void InterfaceItem::resetActiveState(){
	}
