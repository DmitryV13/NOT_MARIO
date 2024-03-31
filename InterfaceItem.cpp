#include "stdafx.h"
#include "InterfaceItem.h"

	void InterfaceItem::render(){
	}
	
	void InterfaceItem::update(){
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

	const int& InterfaceItem::getId() const{
		return id;
	}

	void InterfaceItem::setPositionX(float x){
	}

	void InterfaceItem::setPositionY(float y){
	}

	View InterfaceItem::createLocalView(FloatRect rect, RenderTarget* target) const{
		FloatRect old_view_bounds = FloatRect(
			target->getView().getCenter().x - (target->getView().getSize().x / 2),
			target->getView().getCenter().y - (target->getView().getSize().y / 2),
			target->getView().getSize().x,
			target->getView().getSize().y
		);
		float left{ rect.left };
		float top{ rect.top };
		float width{ rect.width };
		float height{ rect.height };

		if (old_view_bounds.left >= left) {
			float offset = old_view_bounds.left - left;
			if (offset >= width) {
				width = 0;
			}
			else if(offset < width && offset > 0){
				width -= offset;
				left += offset;
			}
		}
		else if (old_view_bounds.left + old_view_bounds.width <= left + width) {
			float offset = left + width - (old_view_bounds.left + old_view_bounds.width);
			if (offset >= width) {
				width = 0;
			}
			else if (offset < width && offset > 0) {
				width -= offset;
			}
		}
		if (old_view_bounds.top >= top) {
			float offset = old_view_bounds.top - top;
			if (offset >= height) {
				height = 0;
			}
			else if (offset < height && offset > 0) {
				height -= offset;
				top += offset;
			}
		}
		else if (old_view_bounds.top + old_view_bounds.height <= top + height) {
			float offset = top + height - (old_view_bounds.top + old_view_bounds.height);
			if (offset >= height) {
				height = 0;
			}
			else if (offset < height && offset > 0) {
				height -= offset;
			}
		}

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
