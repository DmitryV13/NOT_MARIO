#pragma once
#include "InputField.h"

class NumberField: public InputField {
private:
	float min;
	float max;
	bool isFloat;
	void inputLogic(int typed_char) override;
public:
	NumberField(float x, float y, float width_, float height_, const string& input_label_, int text_size_, Color text_color_, bool has_limit_, int limit_);
	NumberField(float x, float y, float width_, float height_, const string& input_label_, int text_size_, bool has_limit_, int limit_);
	~NumberField();

	void setMinMaxType(float min, float max, bool isFloat_);

	void update() override;
};

