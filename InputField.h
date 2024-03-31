#pragma once
#include "InterfaceItem.h"
#include "FormItem.h"
#include "Textarea.h"
#include "FORM_ITEM_STATE.h"
#include "FORM_ITEM_TYPE.h"
#include "INTERFACE_ITEM_TYPE.h"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

using namespace::sf;

class InputField: public InterfaceItem, public FormItem {
protected:
	Text* label;
	Textarea* textarea;
	std::ostringstream input_stream;

	int text_size;
	Color text_color;

	bool chosen;
	bool unpressed;

	RectangleShape shape1;

	bool has_limit;
	bool overflow_x;
	int limit;

	float width;
	float height;
	Vector2f position;

	virtual void inputLogic(int typed_char);
	void deletLastChar();

	InputField(float x, float y, float width_, float height_, const string& input_label_, 
		int text_size_, Color text_color_, bool has_limit_, int limit_, bool multiline);
public:
	InputField();
	InputField(float x, float y, float width_, float height_, const string& input_label_, int text_size_);
	InputField(float x, float y, float width_, float height_, const string& input_label_, int text_size_, 
		Color text_color_, bool has_limit_, int limit_);
	InputField(float x, float y, float width_, float height_, const string& input_label_, int text_size_, 
		bool has_limit_, int limit_);

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;
	string* getString();

	void setVisibility(bool vis);
	void setOverflow(short overflow);
	void setPositionX(float x) override;
	void setPositionY(float y) override;
	void changePosition(float offset_x, float offset_y) override;
	void changeVisibility(float param1, float param2);

	bool itemScroll(float delta) override;
	void formEInput(Event event) override;

	void update() override;
	void render() override;
};



