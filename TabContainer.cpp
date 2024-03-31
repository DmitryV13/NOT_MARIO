#include "stdafx.h"
#include "TabContainer.h"
	
	TabContainer::TabContainer(float x, float y, float width_, float height_)
		:position(Vector2f(x, y)), width(width_), height(height_){
		ii_type = INTERFACE_ITEM_TYPE::TAB_CONTAINER;
		id = GlobalProcessData::getUnicId();
	}

	FloatRect TabContainer::getLocalBounds(){
		return FloatRect(position, Vector2f(width, height));
	}

	FloatRect TabContainer::getGlobalBounds(){
		return FloatRect(position, Vector2f(width, height));
	}

	void TabContainer::setPosition(float x, float y){
		position = Vector2f(x, y);
	}

	void TabContainer::setPositionX(float x){
		setPosition(x , position.y);
	}

	void TabContainer::setPositionY(float y){
		setPosition(position.x, y);
	}

	void TabContainer::addTab(Group* tab){
		if (tabs.empty())
			current_tab = 0;
		tabs.push_back(tab);
	}

	void TabContainer::changePosition(float offset_x, float offset_y){
		setPosition(position.x + offset_x, position.y + offset_y);
		for (auto i : tabs) {
			i->changePosition(offset_x, offset_y);
		}
	}

	void TabContainer::changeCurrentTab(float tab_index, float param2){
		current_tab = static_cast<int>(tab_index);
	}

	void TabContainer::update(){
		Vector2f mouse_pos = GlobalProcessData::getMousePos();
		FloatRect view_cords = GlobalProcessData::getViewCords();

		if (!tabs.empty()) {
			tabs[current_tab]->update();
		}
	}

	void TabContainer::render(){
		if (!tabs.empty()) {
			tabs[current_tab]->render();
		}
	}
