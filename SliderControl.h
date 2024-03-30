#pragma once
#include "InterfaceItem.h"
#include "FormItem.h"
#include "FORM_ITEM_STATE.h"
#include "FORM_ITEM_TYPE.h"

class SliderControl: public InterfaceItem, public FormItem{
private:
	Text* label;
	string s_value;
	float* f_value;
	bool isStatic;
	
	RectangleShape shape1;
	RectangleShape scale;
	CircleShape slider;

	float slider_offset_x;
	float mouse_pressed_pos_x;
	bool chosen;

	float min;
	float max;

	float width;
	float height;
	Vector2f position;

	void changeValue();
public:
	SliderControl(float x, float y, float width_, float height_, const string& input_label_, Font* font_);

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;

	void setMinMaxType(float min_, float max_);
	void setValueType(float* value_, bool isStatic_);
	void setPositionX(float x) override;
	void setPositionY(float y) override;
	void changePosition(float offset_x, float offset_y) override;

	void scrollSlider(float mouse_pos_x);

	void render(RenderTarget* target) override;
	void update(Vector2f mouse_pos, FloatRect view_cords) override;
};

