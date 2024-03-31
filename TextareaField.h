#pragma once
#include "InputField.h"

class TextareaField: public InputField{
private:
public:
	TextareaField(float x, float y, float width_, float height_, const string& input_label_, int text_size_, Color text_color_, bool has_limit_, int limit_);
	TextareaField(float x, float y, float width_, float height_, const string& input_label_, int text_size_, bool has_limit_, int limit_);
};

