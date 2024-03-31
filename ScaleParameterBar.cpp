#include "stdafx.h"
#include "ScaleParametrBar.h"


	ScaleParameterBar::ScaleParameterBar(){
		ii_type = INTERFACE_ITEM_TYPE::SCALE_PARAMETER_BAR;
		id = GlobalProcessData::getUnicId();
	}
	
	ScaleParameterBar::ScaleParameterBar(float x, float y, float width, float height, float* resource_, float max_value_, TextureManager* t_manager, Warehouse* w_object, string name)
		: resource(resource_), max_value(max_value_), position(Vector2f(x, y)){
		ii_type = INTERFACE_ITEM_TYPE::SCALE_PARAMETER_BAR;
		id = GlobalProcessData::getUnicId();

		shape.setPosition(position); 
		shape.setSize(Vector2f(width, height));

		offset = 6;
		front_bar = w_object->getWarehouseItem(name)->getSpriteInfo().first;
		middle_bar = IntRect(6, offset + front_bar.height, front_bar.width - offset*2, 8);
		back_bar = IntRect(6, offset + front_bar.height * 2, front_bar.width - offset*2, 8);

		scale_bar.setPosition(position);
		scale_bar.setTexture(t_manager->getTexture(w_object->getWarehouseItem(name)->getTMInfo().first, name));
		scale_bar.setTextureRect(w_object->getWarehouseItem(name)->getSpriteInfo().first);

		float scale = (width / scale_bar.getLocalBounds().width) <
			(height / scale_bar.getLocalBounds().height) ?
			(width / scale_bar.getLocalBounds().width) :
			(height / scale_bar.getLocalBounds().height);
		scale_bar.setScale(scale, scale);
		offset *= scale;
	}

	ScaleParameterBar::~ScaleParameterBar(){

	}

	FloatRect ScaleParameterBar::getLocalBounds(){
		return FloatRect(position, Vector2f(shape.getSize().x, shape.getSize().y));
	}

	FloatRect ScaleParameterBar::getGlobalBounds(){
		return FloatRect(position, Vector2f(shape.getSize().x, shape.getSize().y));
	}

	void ScaleParameterBar::setPosition(Vector2f new_position){
		position = new_position;
		shape.setPosition(position);
		scale_bar.setPosition(position);
	}

	void ScaleParameterBar::setPositionX(float x){
		setPosition(Vector2f(x, position.y));
	}

	void ScaleParameterBar::setPositionY(float y){
		setPosition(Vector2f(position.x, y));
	}

	void ScaleParameterBar::changePosition(float offset_x, float offset_y){
		setPosition(Vector2f(position.x + offset_x, position.y + offset_y));
	}

	void ScaleParameterBar::update(){
		Vector2f mouse_pos = GlobalProcessData::getMousePos();
		FloatRect view_cords = GlobalProcessData::getViewCords();

		middle_bar.width = static_cast<float>(*resource) / max_value * back_bar.width;
		shape.setPosition(Vector2f(
			position.x + view_cords.left - view_cords.width / 2,
			position.y + view_cords.top - view_cords.height / 2
		));
		scale_bar.setPosition(Vector2f(
			position.x + view_cords.left - view_cords.width / 2,
			position.y + view_cords.top - view_cords.height / 2
		));
	}

	void ScaleParameterBar::render(){
		RenderTarget* target = GlobalProcessData::getWindow();

		scale_bar.move(Vector2f(
			offset,
			offset
		));
		scale_bar.setTextureRect(back_bar);
		target->draw(scale_bar);

		scale_bar.setTextureRect(middle_bar);
		target->draw(scale_bar);
		scale_bar.move(Vector2f(
			-offset,
			-offset
		));
		scale_bar.setTextureRect(front_bar);
		target->draw(scale_bar);
	}