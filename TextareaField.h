#pragma once
#include "InputField.h"

class TextareaField: public InputField{
private:
	bool overflow_y;
	void  inputLogic(int typed_char) override;
public:
	TextareaField(float x, float y, float width_, float height_, const string& input_label_, Font* font_, int text_size_, Color text_color_, bool has_limit_, int limit_);
	TextareaField(float x, float y, float width_, float height_, const string& input_label_, Font* font_, int text_size_, bool has_limit_, int limit_);

	void update(Vector2f mouse_pos, FloatRect view_cords);
};

