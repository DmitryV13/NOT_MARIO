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

	View InterfaceItem::createLocalView(FloatRect rect, RenderTarget* target) const{
		float left{ rect.left };
		float top{ rect.top };
		float width{ rect.width };
		float height{ rect.height };
		sf::View view;
		view.setSize(width, height);
		view.setCenter(left + (width / 2.f), top + (height / 2.f));
		view.setViewport(sf::FloatRect(
			left / target->getSize().x,
			top / target->getSize().y,
			width / target->getSize().x,
			height / target->getSize().y)
		);
		return view;
	}

	bool InterfaceItem::itemScroll(float delta){
		return false;
	}

	void InterfaceItem::changeChildrenPosition(float offset_x, float offset_y){
	}

	void InterfaceItem::changePosition(float offset_x, float offset_y){
	}

	void InterfaceItem::resetActiveState(){
	}
