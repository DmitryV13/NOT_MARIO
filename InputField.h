#pragma once
#include "InterfaceItem.h"
#include "FormItem.h"
#include "FORM_ITEM_STATE.h"
#include "FORM_ITEM_TYPE.h"
#include "INTERFACE_ITEM_TYPE.h"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

using namespace::sf;

class InputField: public InterfaceItem, public FormItem {
protected:
	Text* input_label;
	Text* input_text;
	std::ostringstream input_stream;
	string* input_str;
	int text_size;
	int efficient_chars;

	Color text_color;

	bool chosen;
	bool unpressed;

	RectangleShape shape;
	RectangleShape shape1;

	bool has_limit;
	bool overflow_x;
	int limit;

	float width;
	float height;
	Vector2f position;

	virtual void  inputLogic(int typed_char);
	void deletLastChar();
public:
	InputField(float x, float y, float width_, float height_, const string& input_label_, Font* font_, int text_size_, Color text_color_, bool has_limit_, int limit_);
	InputField(float x, float y, float width_, float height_, const string& input_label_, Font* font_, int text_size_, bool has_limit_, int limit_);

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;
	string* getSource();

	void setPositionX(float x) override;
	void setPositionY(float y) override;
	void changePosition(float offset_x, float offset_y) override;

	void formEInput(Event event) override;
	void update(Vector2f mouse_pos, FloatRect view_cords) override;
	void render(sf::RenderTarget* target) override;
};



