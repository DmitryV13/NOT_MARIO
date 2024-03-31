#pragma once
#include "InterfaceItem.h"
#include "TextureManager.h"
#include "Warehouse.h"
#include "GeneralInfo.h"

using namespace sf;

class ScaleParameterBar : public InterfaceItem{
private:
	Sprite scale_bar;
	float* resource;
	float max_value;

	IntRect front_bar;
	IntRect middle_bar;
	IntRect back_bar;

	float offset;
	RectangleShape shape;
	Vector2f position;
public:
	ScaleParameterBar();
	ScaleParameterBar(float x, float y, float width, float height, float* resource_, float max_value_, 
		TextureManager* t_manager, Warehouse* w_object, string name);
	~ScaleParameterBar();

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;

	void setPosition(Vector2f new_position);
	void setPositionX(float x) override;
	void setPositionY(float y) override;

	void changePosition(float offset_x, float offset_y) override;

	void update() override;
	void render() override;
};

