#include "stdafx.h"
#include "TextareaField.h"

	TextareaField::TextareaField(float x, float y, float width_, float height_, const string& input_label_,
		int text_size_, Color text_color_, bool has_limit_, int limit_)
		:InputField(x, y, width_, height_, input_label_, text_size_, text_color_, has_limit_, limit_, true) {
		fi_type = FORM_ITEM_TYPE::TEXTAREA_FIELD;

		textarea->setOverflow(ITEM_OVERFLOW::VERTICAL);
	}
	
	TextareaField::TextareaField(float x, float y, float width_, float height_, const string& input_label_, 
		int text_size_, bool has_limit_, int limit_) 
		:InputField(x, y, width_, height_, input_label_, text_size_, Color::Black, has_limit_, limit_, true) {
		fi_type = FORM_ITEM_TYPE::TEXTAREA_FIELD;

		textarea->setOverflow(ITEM_OVERFLOW::VERTICAL);
	}

	TextareaField::~TextareaField(){
	}
